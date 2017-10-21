# Hardware PWM
## Objectives
The goal of this lab was to use hardware techniques to create a PWM that will toggle the brightness of an LED.
## Summary
The lab involved the basic initalization done as always with the addition of a few enables. To begin we set the timer for the PWM by using the SMCLK in up mode, then we set the period by saying TA0CCR0 = 1000, and the duty cyle to 50% using TA0CCR1 = 500. Then using an if statement inside of an infinite loop we are able to determine whether to increment the duty cycle by 100 (10%) or whether to keep the duty cycle the same based on whether or not the button is pressed.
## Code Differences
Pins all change of course, but the line of code "PM5CTL0 &= ~LOCKLPM5;"is required in order to disable the GPIO power-on default high-impedance mode for the 2311 and 6989. The 2311 has no TimerA so TimerB was used for that implementation.