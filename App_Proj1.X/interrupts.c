/*
 * File:   interrupts.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 7:33 PM
 */


#include "xc.h"

void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    T2CONbits.TON = 0;
    
    //TMR2Flag = 1;
    
    return;
}

void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void){
    
    if(IFS1bits.CNIF == 1){
        
        
        
        
    }
    
}