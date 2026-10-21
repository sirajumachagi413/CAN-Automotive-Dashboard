#ifndef ECU1_SENSOR_H
#define	ECU1_SENSOR_H

#include <stdint.h>
#include "digital_keypad.h"
#include <xc.h>

#define _XTAL_FREQ 20000000

#define RPM_ADC_CHANNEL 0x04
#define ENG_TEMP_ADC_CHANNEL 0x06

#define LED_OFF 0
#define LED_ON 1

#define RIGHT_IND_ON() (PORTB = (PORTB | 0xC0))
#define RIGHT_IND_OFF() (PORTB = (PORTB & ~0xC0))
#define LEFT_IND_ON() (PORTB = (PORTB | 0x03))
#define LEFT_IND_OFF() (PORTB = (PORTB & ~0x03))

typedef enum {
    e_ind_off,
    e_ind_left,
    e_ind_right,
    e_ind_hazard
} IndicatorStatus;

extern volatile IndicatorStatus prev_ind_status, cur_ind_status;
extern volatile unsigned char led_state;

void get_rpm(uint8_t *rpm_buff);
IndicatorStatus process_indicator();

#endif