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

#define ADC_MODCLK 0x3

// ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_CKPS   0x1

#define ADC_SHCLK  0xf   // S/H width in ADC module periods = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   1024  // Sample buffer size

// Globals

Uint16 SampleTable1[BUF_SIZE];
Uint16 SampleTable2[BUF_SIZE];

void main(void)
{
    Uint16 i;

    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    InitSysCtrl();

    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
    EDIS;

    // Step 2. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
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

    // Step 5. User specific code, enable interrupts:
    // Clear SampleTable
    for (i=0; i<BUF_SIZE; i++)
    {
        SampleTable1[i] = 0;
        SampleTable2[i] = 0;
    }

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
