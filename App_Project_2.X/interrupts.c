/*
 * File:   interrupts.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 7:33 PM
 */


#include "xc.h"
#include "interrupts.h"
#include "timers.h"

// set timer interrupts for timer 2 subroutine
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    // stopping the timer
    T2CONbits.TON = 0;
    
    return;
}

