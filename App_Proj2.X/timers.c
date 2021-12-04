/*
 * File:   timers.c
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:08 AM
 */


#include "xc.h"
#include "timers.h"
#include "config.h"

void Delay_ms(uint16_t time_ms){
    
    //Computer PR2
    PR2 = time_ms;
    
    //Clearing TMR2
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    
    //Configure T2CON Register
    timer2Config();
    
    //Timer 2 Interrupt Configuration
    timer2InterruptConfig();
    
    Idle();
    
    T2CONbits.TON = 0;
    TMR2 = 0;
    
    return;
}


void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    T2CONbits.TON = 0;
    
    
    return;
}