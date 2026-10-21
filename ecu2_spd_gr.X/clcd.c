/*
 * File:   clcd.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 12:55 PM
 */

#include <xc.h>
#include "clcd.h"

void init_clcd(void)
{
    TRISD=0x00;
    TRISC=TRISC & 0xF8;
    __delay_ms(30); // clcd start up time
    
    /* clcd start up sequence */
    clcd_write(0x33, 0);
    __delay_us(4100);
    clcd_write(0x33, 0);
    __delay_us(100);
    clcd_write(0x33, 0);
    __delay_us(1);
    
    clcd_write(0x02, 0); // return home
    __delay_us(100);
    clcd_write(0x38, 0); // 2 line 5*8 matrix 8 bit
    __delay_us(100);
    clcd_write(0x01, 0); // clear display
    __delay_us(500);
    clcd_write(0x0C, 0); // display on cursor off
    __delay_us(100);
}

void clcd_write(unsigned char byte, unsigned char type)
{
    PORTD = byte;
    PORTCbits.RC1 = type;
    PORTCbits.RC2 = 1;
    PORTCbits.RC2 = 0;
    
    TRISDbits.TRISD7=1;
    PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 0;
    do {
        PORTCbits.RC2 = 1;
        PORTCbits.RC2 = 0;
    } while(PORTDbits.RD7);
    
    PORTCbits.RC0 = 0;
    TRISDbits.TRISD7 = 0;
}

void clcd_print(const unsigned char *data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0')
	{
		clcd_write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(unsigned char data, unsigned char addr)
{
	clcd_write(addr, 0);
	clcd_write(data, 1);
}