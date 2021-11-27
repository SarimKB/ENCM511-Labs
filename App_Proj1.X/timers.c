/*
 * File:   timers.c
 * Author: Sarim
 *
 * Created on October 29, 2021, 4:53 PM
 */


#include "xc.h"
#include "timers.h"

//Global variable keeping track of whether Timer2 has triggered
//uint16_t TMR2Flag = 0;


void Delay_ms(uint16_t time_ms){
    
    //Computer PR2
    PR2 = time_ms;
    
    //Clearing TMR2 and resetting flag
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    
    //Timer 2 Interrupt Configuration
    timer2InterruptConfig();
    
    //Configure T2CON Register
    timer2Config();
    
    Idle();
    // turn off timer, reset TMR2
    T2CONbits.TON = 0;
    TMR2 = 0;
    
    return;
}


