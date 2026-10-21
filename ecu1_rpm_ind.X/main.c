/*
 * File:   main.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 10:17 AM
 */

#include <xc.h>
#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"
#include "digital_keypad.h"
//#include "clcd.h"

int main()
{
    init_digital_keypad();
    init_adc();
    init_can();
//    init_clcd();
    
    uint8_t rpm_buff[4], ind_buff[1];
    uint16_t ind_status = 0;
    
    while(1) {
        get_rpm(rpm_buff);
                
        ind_status = process_indicator();
        ind_buff[0] = ind_status + '0';
        can_transmit(INDICATOR_MSG_ID, ind_buff, 1);
    }
}
