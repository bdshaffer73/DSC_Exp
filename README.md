# DSC_Exp
Experimental code for learning how to use the TMS320F28335 Digital Signal Controller.

# Overview
The project as it stands may or may not work on any particular computer, but likely will not. To run my code, one must have 
Code Composer Studio v7, and must have installed the device header files for the 28335 DSP from TI. Even then, I can't 
gaurantee it will work for anyone besides me.

Anyway, lets get to the interesting stuff.

## Strategy
This project is a modified combination of two projects sourced from TI. The main file is Example_2833xAdcSeqModeTest.c. This project
is able to be deployed to a Delfino 28335 DSP and, using a Peripheral Explorer board, read the inputs from two potentiometers. The onboard
ADC module then converts the voltages from the POTs into usable numbers, in a range from 0 to 4096. 
The DSP also has an onboard enhanced PWM module that can output at a frequency between roughly 1200Hz and 75kHz, at integer division duty cycles.

To accomplish this, I used well defined code from one example project to read in the ADC values. I stored these values, then used them to
calculate a percentage scaling factor for the PWM frequency and duty cycle. I then used well defined code from another project to create
the PWM output.

## Implementation
To calculate the PWM frequency I used the following lines of code, which get the percentage of 'maximum readable voltage' from the potentiometer
and multiply it by the maximum period attainable. EPWM1_PERIOD is eventually passed into the PWM control register to update the output.
I should note that this actually calculates the output period in terms of system clock cycles. The system clock runs at 150MHz, and with 
my settings, the output frequency of the PWM, Fs = 150,000,000 / (2 * EPWM1_PERIOD).
> sf1 = (float32)(SampleA0) / 4096;

> EPWM1_PERIOD = sf1 * 0xffff;

To calculate the PWM frequency I used the following lines of code, which get the percentage of 'maximum readable voltage' from the potentiometer
and multiply it by the maximum period attainable. EPWM1_PERIOD is eventually passed into the PWM control register to update the output.
> sf2 = (float32)(SampleA1) / 4096;

> EPWM1_CMPA = sf2 * EPWM1_PERIOD;

These calculations are performed every time the PWM 'resets', which triggers an interrupt to be called. The ISR then updates the PWM settings.
The PWM 'resets' at the end (or beginning) of every period.

## Demo
I was able to test the system using built in functions in Code Composer, and have created a demonstration viewable here: https://youtu.be/DWemPLxdVSQ.

## Sources
TMS320x2833x Reference Guides: http://www.ti.com/product/TMS320F28335/technicaldocuments
ePWM Reference Guide: http://www.ti.com/lit/ug/sprug04a/sprug04a.pdf
ADC Reference Guide: http://www.ti.com/lit/ug/spru812a/spru812a.pdf

Code Project examples can be sourced through CCSv7. The projects I used are:
* Example_2833xAdcSeqModeTest
* Example_2833xEPwmUpDownAQ
The PWM project that I used, however, was already modified by a professor in my department. The modifications simply removed
the second and third PWM control, and added some action to the ISR. This project directly from TI should work just the same.

I also used libraries built for the 2833x family. These were installed by a program from the tutorial disk included with the Explorer Kit that the DSP comes in. However, I believe the files installed when importing the projects from the CCSv7 Resource Explorer will work equally as well, if not identically.
