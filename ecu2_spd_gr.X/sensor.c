/*
 * File:   sensor.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 12:55 PM
 */

#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "digital_keypad.h"
//#include "uart.h"

extern uint16_t gear;

uint16_t get_speed()
{
    // Implement the speed function
    if(gear == 0) return 0;
    else return (read_adc(SPEED_ADC_CHANNEL)/10.23);
}

void spd_to_char(uint16_t speed, uint8_t *spd_buff)
{
    spd_buff[2] = (speed%10) + '0';
    speed = speed/10;
    short i = 1;
    while(speed > 0 && i >= 0) {
        spd_buff[i--] = (speed%10) + '0';
        speed = speed/10;
    }
    while(i >= 0) spd_buff[i--] = ' ';
}

void get_gear_pos()
{
    // Implement the gear function
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    if((key == SWITCH1) && (gear < 6)) gear++;
    else if((key == SWITCH2) && (gear > 0)) gear--;
}