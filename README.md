# DSC_Exp : Experimenting with the Texas Instruments TMS320F28335 Digital Signal Controller

What is a Digital Signal Controller, you ask? It's like a general purpose computer, except it's specially designed for digital signal processing. This particular unit comes with a handy Peripheral Explorer board which includes a multi-channel Analogue to Digital Converter (ADC), a multi-channel Pulse-Width Modulation (PWM) output, two potentiometers and lots of other things which I'm not terribly interested in. The general purpose of the system is this: The world is made of analogue systems, and computers are typically digital. But general purpose computers aren't very power efficient and aren't especially designed to work with analoge signals. This system utilizes specific hardware to sample analogue signals (DAC), process it (CPU running C++), and do something with it (LEDs, PWM, etc.) all at very low power (5W or less).

# The basics

To get started with the TMS320F28335, or 28335 for short, you need a programming IDE (Integrated Development Environment) that is configured to work with this DSP (DSC or DSP, they're very similar). It helps to have the particular device headers too, as that will save you A LOT of writing and errors. For this project and future projects, I will be using Code Composer Studio v7, but other programs like Simulink may work. The unit I am using is borrowed from my department, and came with some tutorials, example labs, and the device header files.

Once you have installed CCS7 and the headers for this particular device, you're ready to code, which is easier said than done. Programming this unit is simple, but also incredibly confusing. You may want to draw out schematics to understand how everything works. To configure **all** of the peripherals and the internal system functions, you must toggle specific bits in specific registers. The registers are generally named and the values to set them to aren't clearly specified in the supplied libraries. My best method of determining how to set the registers is to refer to the PDFs and PowerPoint slides provided in the tutorials, which include the elaborated names of each register and what its settings correspond to.

And that's it! That's the basics of setting up this unit. Each register bit corresponds to a specific peripheral or function, so initialization simply requires setting the correct bits for your needs.

# Programming

This unit is programmed using C/C++. The included device headers are very useful, and are used in my example test. To test my understanding, I wrote and deployed a simple program to blink the LEDs in a pattern. The actual logic for my code is very short; my goal was to demonstrate an understanding of how to interact with the hardware and configure it for a simple task. The complexity of the task does not greatly matter to demonstrate this; the hardware is fairly simple and only acts as an interface with the real world. This interface however is why I chose to work with the unit.

The code I wrote can be found in the file `main.c` within the project folder. To implement my simple blink system, I needed to develop an understanding of the GPIO setup process and the WatchDog system. I also learned a bit about the clocking system (there are 3 seperate clock signals onboard) because it is used when working with everything.

Viewing the GPIO from the perspective of the 28335, every register is simply generic. The Explorer board determines the GPIO pin assigned to each LED, which determined the pin numbers referenced in set_bit().

InitSystem() sets up the peripheral clocks and enables the WatchDog and GPIO.

GPIOSetup() clears all GPIO registers, then enables the LEDs.

delay_loop() simply resets the WatchDog (or else the system would error due to the WatchDog skipping the wait-loop) every loop for many cycles. The delay length depends on how fast the blink should go.

# Challenges I faced

The documentation for the 28335 is not friendly to newcomers. I could not find anywhere that explained what is necessary to start a new, simple project and get it deployable. Instead I read through many pages of dense documentation (and asked for a little help) and pieced together everything I wrote above about getting started. I also realized after setting my goals that "record audio sample; filter it; play it back" is much more difficult on this system than in, say, Matlab. More realistic goals for now would be "Map register setup; Read Potentiometers; Output PWM signal."

# References

Sample lab solutions by Frank Bormann, 2009. Part of the C2000 Teaching Materials, Tutorials and Applications CD that came with my kit. Published by Texas Instruments.

Header files, also from that CD.

Documentation of all the basic functions, also from that CD.

Getting Started with CCS7, https://youtu.be/Ppm8tSV7krQ?list=PL3NIKJ0FKtw4-YIENLeN4PAxR6741ndAS


