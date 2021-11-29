/*
 * File:   interrupts.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 7:33 PM
 */


#include "xc.h"
#include "interrupts.h"
#include "timers.h"
#include "ChangeClk.h"
#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED_out LATBbits.LATB8

// set timer interrupts for timer 2 subroutine
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    // stopping the timer
    T2CONbits.TON = 0;
    
    return;
}

