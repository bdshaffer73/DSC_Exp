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

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

typedef struct
{
   volatile struct EPWM_REGS *EPwmRegHandle;
   Uint16 EPwm_CMPA_Direction;
   Uint16 EPwm_CMPB_Direction;
   Uint16 EPwmTimerIntCount;
   Uint16 EPwmMaxCMPA;
   Uint16 EPwmMinCMPA;
   Uint16 EPwmMaxCMPB;
   Uint16 EPwmMinCMPB;
}EPWM_INFO;

void InitEPwm1Example(void);
interrupt void epwm1_isr(void);

EPWM_INFO epwm1_info;

#define EPWM1_TIMER_TBPRD  2000  // Period register
#define EPWM1_MAX_CMPA     1950
#define EPWM1_MIN_CMPA       50
#define EPWM1_MAX_CMPB     1950
#define EPWM1_MIN_CMPB       50

// ADC Module Clock
#define ADC_MODCLK 0x3

// ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_CKPS   0x1

#define ADC_SHCLK  0xf   // S/H width in ADC module periods = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   128  // Sample buffer size

//Keep track of PWM counter direction
#define EPWM_CMP_UP   1
#define EPWM_CMP_DOWN 0

// Globals

Uint16 SampleTable1[BUF_SIZE];
Uint16 SampleTable2[BUF_SIZE];
float32 sf1;
float32 sf2;

// Ben's Variable Declaration //
Uint16  EPWM1_PERIOD = 3000;
Uint16  EPWM1_CMPA = 1425;
Uint16  EPWM1_CMPB = 1575;
Uint16  EPWM1_CLK_DIV = 0;

void main(void)
{
    Uint16 i;

    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    InitSysCtrl();

    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;    // HSPCLK = SYSCLKOUT/ADC_MODCLK
    EDIS;

    // Step 2. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    InitEPwm1Gpio();
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table. This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    InitPieVectTable();

    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_isr;
    EDIS;

    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    InitAdc();  // For this example, init the ADC

    // Specific ADC setup for this project:
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
    AdcRegs.ADCMAXCONV.all = 0x0001;         // Setup 2 conversions
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;   // Convert channel 0
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;   // Convert channel 1
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    // Step 5. User specific code, enable interrupts:
    // Clear SampleTable

    IER |= M_INT3;

    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;

    for (i=0; i<BUF_SIZE; i++)
    {
        SampleTable1[i] = 0;
        SampleTable2[i] = 0;
    }

    EINT;
    ERTM;

    // Start SEQ1
    AdcRegs.ADCTRL2.all = 0x2000;

    // Take ADC data and log it in the SampleTable arrays
    for(;;)
    {
        for (i=0; i<AVG; i++)
        {
            // Wait for interrupt
            while (AdcRegs.ADCST.bit.INT_SEQ1== 0) 
            {
                
            }
            AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
            SampleTable1[i] =((AdcRegs.ADCRESULT0>>4) );
            SampleTable2[i] =((AdcRegs.ADCRESULT1>>4));
        }
    }
}

interrupt void epwm1_isr(void)
{
    // *****  CHANGE VALUES HERE  ***** //
        // CHANGE THE PERIOD/FREQUENCY OF THE DSP
       sf1 = (float32)(SampleTable1[0]) / 4096;
       sf2 = (float32)(SampleTable2[0]) / 4096;
       EPWM1_PERIOD = sf1 * 0xffff;
       EPWM1_CMPA = sf2 * EPWM1_PERIOD;

       EPwm1Regs.TBPRD = EPWM1_PERIOD;           // Set timer period 801 TBCLKs

        // CHANGE THE DUTY CYCLE OF PWM1A
       EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA;     // Set compare A value

        // CHANGE THE DUTY CYCLE OF PWM1B
       EPwm1Regs.CMPB = EPWM1_CMPB;               // Set Compare B value

        // CHANGE THE DUTY CYCLE OF PWM1B
       EPwm1Regs.TBCTL.bit.CLKDIV = EPWM1_CLK_DIV;

    // ***** DO NOT CHANGE VALUES AFTER THIS  ***** //
    // ***** UNLESS YOU LIKE PUZZLES! *****//


   // Clear INT flag for this timer
   EPwm1Regs.ETCLR.bit.INT = 1;
   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

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
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on event A, up count
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM1A on event A, down count

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
