#include <msp430.h>


int Push_Button;
void main(void){


    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1IE |= BIT1;
    P1IES |= BIT1;
    P1IFG &= ~BIT1;

    // Timer0_A
    TA0CCR0 |= 1000;                    // Period
    TA0CCR1 |= 500;                   // Duty cycle
    TA0CCTL1 |= OUTMOD_7;           // reset/set
    TA0CTL |= TASSEL_2 + MC_1;      // SMCLK, Up Mode]


}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    if (Push_Button == 0)
{
    TA0CCR1 = TA0CCR1+100;
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
    P1IES ^= BIT1;
    P1IE |= BIT1;
    P1IFG &= ~(BIT1);
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_1A1(void) {
   TA1CTL &= ~(MC1 | MC0);
   P1IE |= BIT1;
 TA1CCTL0 &= ~CCIFG;
}
