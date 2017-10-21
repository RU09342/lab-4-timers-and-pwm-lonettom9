#include <msp430.h>

int main(void) {
 WDTCTL = WDTPW + WDTHOLD;



 P1DIR |= BIT0;
 P1OUT &= ~BIT0;

 P5DIR  &= ~BIT5;  //button as input
 P5OUT |= BIT5;
 P5REN |= BIT5;

 TA0CCR0 |= 1000;                    // period
 TA0CCR1 |= 500;                   // duty
 TA0CCTL1 |= OUTMOD_7;           // reset/set
 TA0CTL |= TASSEL_2 + MC_1 + TACLR;   // SMCLK, Up Mode

 while (1)
 {
     if((P5IN&BIT5) != BIT5)
     {
         P1OUT |= BIT0;
         if(TA0CCR1 == 100)
         {
             TA0CCR0 = 0;
             TA0CCR1 = 0;
             TA0CCR0 = 100;
         }
         else
         {

             TA0CCR1 = TA0CCR1 + 100;

         }
     }
     else P1OUT &= ~BIT0;

 }
}
