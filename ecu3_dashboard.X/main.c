/*
 * File:   main.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 4:47 PM
 */

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
#include "timer0.h"
//#include "isr.h"

void init_leds()
{
//    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    TRISB = 0x00;
    PORTB = 0x00;
}

void init_config(void)
{
    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
    // Initialize CLCD and CANBUS
    init_clcd();
    init_leds();
    init_can();
}

uint8_t rpm[5] = "    ", indicator[4] = "   ", speed[4] = "   ", gear[2] = " ", toggle = '0', blink = '0';
uint16_t led_status = 0;

void main(void) {
    init_config();
    
    uint16_t msg_id = 0;
    uint8_t data[5], len = 0;  
    
    clcd_print("GR SPD: RPM: IND", LINE1(0));
    while (1) {
        // Read CAN Bus data and handle it
        can_receive(&msg_id, data, &len);

        process_canbus_data(msg_id, data, len);

        indicator_light();
        len = 0;
    }
    return;
}
