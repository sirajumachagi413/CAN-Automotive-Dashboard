/*
 * File:   main.c
 * Author: Edwin Shaji Varghese
 *
 * Created on 19 April, 2026, 12:54 PM
 */

#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "digital_keypad.h"
#include "clcd.h"
//#include "uart.h"

uint16_t gear = 0;

int main()
{
    //Call the functions
    init_adc();
    init_digital_keypad();
    init_can();
//    init_clcd();
    
    uint16_t speed;
    uint8_t spd_buff[3], gr_buff[1];
    
    while(1) {
        get_gear_pos();
        if(gear == 0) gr_buff[0] = 'N';
        else if(gear == 6) gr_buff[0] = 'R';
        else    gr_buff[0] = gear + '0';
        
        speed = get_speed();
        spd_to_char(speed, spd_buff);
        
        can_transmit(GEAR_MSG_ID, gr_buff, 1);
        __delay_ms(50);
        can_transmit(SPEED_MSG_ID, spd_buff, 3);
        __delay_ms(50);
    }
}