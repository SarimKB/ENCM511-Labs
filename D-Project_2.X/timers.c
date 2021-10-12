/*
 * File:   timers.c
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:08 AM
 */


#include "xc.h"
#include "timers.h"

//Global variable keeping track of whether Timer2 has triggered
uint16_t TMR2Flag = 0;


void Delay_ms(uint16_t time_ms){
    
    //Configure Clock
    
    
    //Configure T2CON Register
    timer2Config();
    
    //Clearing TMR2
    TMR2 = 0;
    
    //Timer 2 Interrupt Configuration
    timer2InterruptConfig();
    
    //Computer PR2
    
    
    Idle();
}


void Delay_us(uint16_t time_us){
    
    //Configure Clock
    
    
    //Configure T2CON Register
    timer2Config();
    
    
    
    
    
}


void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    T2CONbits.TON = 0;
    
    TMR2Flag = 1;
    
}