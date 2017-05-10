//###########################################################################
// $TI Release: F2833x Support Library v2.00.00.00 $
// $Release Date: Wed Jan 25 16:04:10 CST 2017 $
// $Copyright:
// Copyright (C) 2009-2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

/**
 * Code adapted from Example_2833xAdcSeqModeTest.c, published by Texas Instruments
 *
 * Author: Ben Shaffer @ shaffebd@miamioh.edu
 */

/*
 * All of these defines are arbitrarily named something that makes sense.
 * Since the names don't really matter, I kept them the same as from the example
 * project that I borrowed code from. They're pretty much essential no matter the code
 * structure.
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//PWM settings
typedef struct {
   volatile struct EPWM_REGS *EPwmRegHandle;
   Uint16 EPwm_CMPA_Direction;
   Uint16 EPwm_CMPB_Direction;
   Uint16 EPwmTimerIntCount;
   Uint16 EPwmMaxCMPA;
   Uint16 EPwmMinCMPA;
   Uint16 EPwmMaxCMPB;
   Uint16 EPwmMinCMPB;
}EPWM_INFO;
EPWM_INFO epwm1_info;

//PWM setup and modification functions
void InitEPwm1Example(void);
interrupt void epwm1_isr(void);

// PWM Module settings
#define EPWM1_TIMER_TBPRD  2000  // Period register
#define EPWM1_MAX_CMPA     1950
#define EPWM1_MIN_CMPA       50
#define EPWM1_MAX_CMPB     1950
#define EPWM1_MIN_CMPB       50

// ADC Module Clock
#define ADC_MODCLK 0x3  //Modifies the clock signal so the ADC can run slower

// ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_CKPS   0x1  //Don't know what this does

#define ADC_SHCLK  0xf   // S/H width in ADC module periods = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset

//Keep track of PWM counter direction
#define EPWM_CMP_UP   1
#define EPWM_CMP_DOWN 0

/*
 * Used to store the ADC readings, calculate a scaling factor for the PWM,
 * then store the PWM settings to be updated.
 */
// Globals
Uint16 SampleA0 = 0;    //Sample 1, from ADC A. I only need one value from it per S/H cycle.
Uint16 SampleA1 = 0;    //Same as Sample 1.
float32 sf1;    //Stores a percentage that is used to set the PWM frequency on a scale of Min to Max.
float32 sf2;    //Stores a percentage that is used to set the PWM duty cycle on a scale of 0 to PRD.
Uint16  EPWM1_PERIOD = 150;   //PWM period, in terms of system clocks. Exact output period depends on several parameters.
Uint16  EPWM1_CMPA = 0;     //PWM comparison level, aka duty cycle.
Uint16  EPWM1_CMPB = 0;     //Irrelevant to this project, but needed.
Uint16  EPWM1_CLK_DIV = 0;  //Irrelevant to this project, but needed.

//Main just gets everything running. The ISR and infinite loop are where the action happens.
void main(void)
{
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    InitSysCtrl();

    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;    // HSPCLK = SYSCLKOUT/ADC_MODCLK
    EDIS;

    // Step 2&3. Initialize GPIO pins for PWM, disable CPU interupts,
    // initialize PIE vector table, clear all interrupts.
    InitEPwm1Gpio();
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    InitPieCtrl();

    // Clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table. This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    InitPieVectTable();

    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_isr;    //Set my ISR to be run rather than the default.
    EDIS;

    // Step 4. Initialize the ADC.
    // This function is found in DSP2833x_InitPeripherals.c
    InitAdc();

    // Specific ADC setup for this project:
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
    AdcRegs.ADCMAXCONV.all = 0x0001;         // Setup 2 conversions
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;   // Convert channel 0
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;   // Convert channel 1
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run

    // Disables the PWM clock so it isn't running while we set it up.
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    // Configure the PWM to work.
    InitEPwm1Example();

    // Start the clock again. PWM will now run with whatever settings it has.
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    // Step 5. User specific code, enable interrupts,

    // Clear SampleTable
    IER |= M_INT3;

    // Enables PWM Interrupt in the PIE vector table.
    // Group 3 interrupts 1 through 3.
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;

    // Enables global interrupts and higher priority real-time debug events.
    EINT;
    ERTM;

    // Start ADC Sequencer 1
    AdcRegs.ADCTRL2.all = 0x2000;

    // Take ADC data and log it in the Sample variables
    Uint16 i;
    for(;;)
    {
        for (i=0; i<AVG; i++)
        {
            // Wait for interrupt
            while (AdcRegs.ADCST.bit.INT_SEQ1== 0) 
            {
                
            }
            AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
            SampleA0 =((AdcRegs.ADCRESULT0>>4));    //Saves the ADC A0 reading
            SampleA1 =((AdcRegs.ADCRESULT1>>4));    //Saves the ADC A1 reading
        }
    }
}

// My code.
interrupt void epwm1_isr(void) {

    //Calculates the scaling factor for the PWM frequency.
    //Read value / Max value = % of max period
    sf1 = (float32)(SampleA0) / 4096;

    //Calculates the scaling factor for the PWM duty cycle.
    //Read value / Max value = % of period
    sf2 = (float32)(SampleA1) / 4096;

    /*
     * Calculates actual period in terms of system clock cycles.
     * System clock runs at 150MHz. PWM frequency is:
     * Fs = SYSCLK / (2 * TBPRD)
     * So, as SampleA1 goes up, Period goes up, and output frequency drops.
     */
    EPWM1_PERIOD = sf1 * 0xffff;

    /*
     * Calculates actual duty cycle in % of period.
     * If TBPRD = 3000 and sf2 = .5, then the duty
     * cycle (CMPA) = 1500. According to InitEPwm1Example(),
     * the PWM output is turned on when the compare value is
     * passed and the PWM module is counting down. Vice versa
     * for turning it off.
     */
    EPWM1_CMPA = sf2 * EPWM1_PERIOD;

    // Set PWM1 period in TBCLKs
    EPwm1Regs.TBPRD = EPWM1_PERIOD;

    // Set the duty cycle of PWM A1
    EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA;

    //Unmodified past here.================

    // Clear INT flag for this timer
   EPwm1Regs.ETCLR.bit.INT = 1;
   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

// Borrowed entirely from one of Dr. Scott's labs.
void InitEPwm1Example()
{
   // Setup TBCLK
   EPwm1Regs.TBPRD = EPWM1_PERIOD;           // Set timer period 801 TBCLKs
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

   // Set Compare values
   EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA;     // Set compare A value
   EPwm1Regs.CMPB = EPWM1_CMPB;               // Set Compare B value

   // Setup counter mode
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   // Setup shadowing
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Clear PWM1A on event A, up count
   EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;           // Set PWM1A on event A, down count

   EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;             // Set PWM1B on event B, up count
   EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;           // Clear PWM1B on event B, down count

   // Interrupt where we will change the Compare Values
   //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;      // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                 // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;            // Generate INT on 1st Event

   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct ePWM registers
   epwm1_info.EPwm_CMPA_Direction = EPWM_CMP_UP;   // Start by increasing CMPA &
   epwm1_info.EPwm_CMPB_Direction = EPWM_CMP_DOWN; // decreasing CMPB
   epwm1_info.EPwmTimerIntCount = 0;               // Zero the interrupt counter
   epwm1_info.EPwmRegHandle = &EPwm1Regs;          // Set the pointer to the ePWM module
   epwm1_info.EPwmMaxCMPA = EPWM1_MAX_CMPA;        // Setup min/max CMPA/CMPB values
   epwm1_info.EPwmMinCMPA = EPWM1_MIN_CMPA;
   epwm1_info.EPwmMaxCMPB = EPWM1_MAX_CMPB;
   epwm1_info.EPwmMinCMPB = EPWM1_MIN_CMPB;

}
