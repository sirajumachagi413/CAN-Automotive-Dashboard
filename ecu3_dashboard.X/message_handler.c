/*
 * File:   message_handler.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 4:47 PM
 */

#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

extern uint8_t rpm[5], indicator[4], speed[4], gear[2];
extern uint8_t toggle, blink;
extern uint16_t led_status;

volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    for(uint8_t i = 0; i < 3; i++)
        speed[i] = data[i];
    speed[3] = '\0';
    clcd_print(speed, LINE2(3));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    gear[0] = data[0];
    gear[1] = '\0';
    clcd_print(gear, LINE2(1));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    for(uint8_t i = 0; i < 4; i++)
        rpm[i] = data[i];
    rpm[4] = '\0';
    clcd_print(rpm, LINE2(8));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    if(data[0] == '0'){
        indicator[0] = ' ';
        indicator[1] = '-';
        indicator[2] = ' ';
        led_status = 0;
        blink = '0';
    }
    else if(data[0] == '1'){
        indicator[0] = '<';
        indicator[1] = '-';
        indicator[2] = ' ';
        led_status = 1;
        blink = '1';
    }
    else if(data[0] == '2'){
        indicator[0] = ' ';
        indicator[1] = '-';
        indicator[2] = '>';
        led_status = 2;
        blink = '1';
    }
    else if(data[0] == '3'){
        indicator[0] = '<';
        indicator[1] = '-';
        indicator[2] = '>';
        led_status = 3;
        blink = '1';
    }
    indicator[3] = '\0';
    clcd_print(indicator, LINE2(13));
}

void process_canbus_data(uint16_t msg_id, uint8_t *data, uint8_t len) 
{   
    switch(msg_id) {
        case RPM_MSG_ID:
            handle_rpm_data(data, len);
            break;
        case INDICATOR_MSG_ID:
            handle_indicator_data(data, len);
            break;
        case SPEED_MSG_ID:
            handle_speed_data(data, len);
            break;
        case GEAR_MSG_ID:
            handle_gear_data(data, len);
            break;
    }
}

void indicator_light(void)
{
    if(led_status == 0 || toggle == '0')
        PORTB = 0X00;
    else if(led_status == 1 && toggle == '1')
        PORTB = 0X03;
    else if(led_status == 2 && toggle == '1')
        PORTB = 0XC0;
    else if(led_status == 3 && toggle == '1')
        PORTB = 0XC3;
}