
#include <msp430.h>


int Push_Button;
void main(void){


    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer



    P1DIR |= BIT0;

    P5REN |= BIT5;
    P5OUT |= BIT5;
    P5IE |= BIT5;
    P5IES |= BIT5;
    P5IFG &= ~BIT5;

    // Timer0_A
    TA0CCR0 |= 1000;                    // Period
    TA0CCR1 |= 500;                   // Duty cycle
    TA0CCTL1 |= OUTMOD_7;           // reset/set
    TA0CTL |= TASSEL_2 + MC_1;      // SMCLK, Up Mode]

    // Timer1_A
    TA1CCR0 |= 4000;                    // Counter value
    TA1CCTL0 |= CCIE;               // Enable Timer1_A interrupts
    TA1CTL |= TASSEL_2 + MC_1;      // SMCLK, Up Mode (Counts to TA1CCR0)

    _BIS_SR(LPM0_bits + GIE);       // Enter Low power mode 0 with interrupts enabled


}

#pragma vector=PORT5_VECTOR
__interrupt void PORT_5(void)
{
    if (Push_Button == 0)
{
    TA0CCR1 = TA0CCR1+100;
    TA1CCTL0 = CAP;
    Push_Button = 1;
    P1OUT ^=  BIT0;
    if (TA0CCR1 == 1100)
                TA0CCR1 = 0;

}
else if (Push_Button == 1)
{

    TA0CCR1 = TA0CCR1;
    P1OUT &=~  BIT0;
    Push_Button = 0;
}
    P5IES ^= BIT5;
    P5IE |= BIT5;
    P5IFG &= ~(BIT5);
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_1A1(void) {
   TA1CTL &= ~(MC1 | MC0);
   P5IE |= BIT5;
 TA1CCTL0 &= ~CCIFG;
}
