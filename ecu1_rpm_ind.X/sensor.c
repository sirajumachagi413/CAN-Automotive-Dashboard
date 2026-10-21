/*
 * File:   sensor.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 10:18 AM
 */

#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"

static uint8_t pkey = SWITCH4;

void get_rpm(uint8_t *rpm_buff)
{
    //Implement the rpm function
    uint16_t rpm = (read_adc(CHANNEL4)*60)/10.23;
    rpm_buff[3] = (rpm%10)+'0';
    rpm = rpm/10;
    short i = 2;
    while(rpm > 0 && i>= 0) {
        rpm_buff[i--] = (rpm%10)+'0';
        rpm = rpm/10;
    }
    while(i >= 0) {
        rpm_buff[i--] = ' ';
    }
    can_transmit(RPM_MSG_ID, rpm_buff, 4);
}


IndicatorStatus process_indicator()
{
    //Implement the indicator function
    uint8_t key = read_digital_keypad(STATE_CHANGE);
    if(key != 0XFF && key != pkey) pkey = key;
    if(pkey == SWITCH1) return e_ind_left;           //1
    else if(pkey == SWITCH2) return e_ind_right;     //2
    else if(pkey == SWITCH3) return e_ind_hazard;    //3
    else if(pkey == SWITCH4) return e_ind_off;       //0
    return e_ind_off;
}