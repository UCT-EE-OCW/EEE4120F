# Prac 4
For this practical,  it is important to complete the tutorial in order to get acquainted with the tools required to complete the practical.
It is also imperative that you read through the wiki.  Operation of Vivado can be intimidating at first use.  The Wiki has been carefully written to include all you need for the practicals.

For the prac manual, see [http://ocw.ee.uct.ac.za/courses/EEE4120F/Practicals.html](the course practicals page)
The Vivado Wiki page can be found [http://wiki.ee.uct.ac.za/Xilinx_Vivado](here).

## Files
* TLM

  The top level module, called "Clock.v" in the source files on GitHub, contains the primary logic for your wall clock and allows you to implement I/O and other modules.
  It's important you leave the signals and registers as they are in this file, as this is what will be used in the automatic testbenches to mark your implementation.
* Delay_Reset

   It's also useful as many components require a set up time. So by using a delayed reset signal, we can cater for reset times of peripherals.
* Seven-Segment Driver

   This module takes 4 BCD values and displays them on the seven segment display.
* Decoder

    Used by the Seven-Segment Driver to decode decimal to the appropriate cathode pins.
* Debounce

   A debounce module you'll need to implement in order to debounce button presses.
* PWM

   A module you'll need to implement in order to give the seven segment displays changing brightness. This can be tricky, it's suggested you leave it for last.
