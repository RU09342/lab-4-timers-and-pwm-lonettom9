#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR  |= BIT0;                     // Set output Direction
    P1REN  |= BIT1;                   // Enables resistor for P1.1
    P1OUT  = BIT1;                    // Makes resistor P1.1 a pull up
    P1IE |= BIT1;
    P1IES = 0;                     // Interrupts when 1.1 is pressed or low to high transition
    P1IFG &= ~BIT1;                   // Clear interrupt flag
    TB0CCTL0 = 0x0010;                  // Enables Capture/compare register for interrupt of timer A0
    TB0CCR0 = 60000;                    // Set value for Timer A0 to count up to
    TB0CTL = TBSSEL_2 + MC_0;           // Timer_A Control Register - SMCLK high frequency clock, timer stopped

        __enable_interrupt();

        __bis_SR_register(LPM0 + GIE);      // Low Power Mode w/ general interrupts enabled

    }

    // Interrupt Service Routine 1 which toggles on the LED on the release of the Button and starts timer a to act as a delay
    #pragma vector = PORT1_VECTOR
    __interrupt void Interrupt_1(void)
    {
        P1OUT ^= BIT0;                      // Toggle LED
        P1IE &= ~BIT1;                    // reset interrupt
        TB0CTL = TBSSEL_2 + MC_1;           // Timer_A Control Register - SMCLK high frequency clock, Up
    }

    // Interrupt Service Routine 2 which stops Timer A0 and resets the interrupt
    #pragma vector=TIMER0_B0_VECTOR
    __interrupt void Interrupt_2(void)
    {
        TB0CTL = MC_0;                      // Stop timer
        P1IE |= BIT1;                     // Interrupt enable set to BUTTON
        P1IFG &= ~BIT1;                     // Clear interrupt flag
    }
