/*
 * File:   timers.h
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:09 AM
 */


#include "xc.h"

//Time delay in milliseconds
void Delay_ms(uint16_t time_ms);

//Timer 2 ISR
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void);
