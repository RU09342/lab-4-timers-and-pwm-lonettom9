# Debouncing
## Objective
The objective was to use timers and interrupts to implement debouncing techniques, instead of previous methods such as infinite loops.
## Summary
The debouncing code was designed for the same functionality as toggling an LED with a button. The major difference is that we are now using timers and interrupts to implement the debounce tactic. By using two interrupts and a timer we achieve the goal. The clock doesnt start until we go into the interrupt. This is the most efficient way to debounce so far.
## Board Differences
Pins all change of course, but the line of code "PM5CTL0 &= ~LOCKLPM5;"is required in order to disable the GPIO power-on default high-impedance mode for the 2311 and 6989. The 2311 has no TimerA so TimerB was used for that implementation.