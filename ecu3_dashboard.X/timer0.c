/*
 * File:   timer0.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 4:48 PM
 */

#include <stdint.h>
#include <xc.h>
#include "timer0.h"

extern uint8_t toggle, blink;
static unsigned int count = 0;

void init_timer0(void) {
    /*
     * Setting instruction cycle clock (Fosc / 4) as the source of
     * timer0
     */
    /*Setting 8 bit timer register*/
    T08BIT = 1;
    /* Selecting internal clock source */
    T0CS = 0;
    /* Enabling timer0*/
    TMR0ON = 1;
    /* disabling prescaler*/
    PSA = 1;
    TMR0 = 6;
    /* Clearing timer0 overflow interrupt flag bit */
    TMR0IF = 0;
    /* Enabling timer0 overflow interrupt */
    TMR0IE = 1;
}

void __interrupt() isr(){
    if(TMR0IF) {
        TMR0=TMR0+8;
        if(blink == '1') {
            count++;
            if(count < 10000)
                toggle = '1';
            else if(count < 20000)
                toggle = '0';
            else
                count = 0;
        }
        else {
            count = 0;
            toggle = '0';
        }
        TMR0IF=0;
    }
}