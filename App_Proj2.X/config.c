/*
 * File:   config.c
 * Author: Sarim
 *
 * Created on November 22, 2021, 1:15 PM
 */

#include "xc.h"
#include "config.h"

void IOinit(void){
    
    //Setting Inputs
    TRISAbits.TRISA2 = 1;   //RA2 (PB1)
    TRISAbits.TRISA4 = 1;   //RA4 (PB2)
    TRISBbits.TRISB4 = 1;   //RB4 (PB3)
    
    
    return;
}

void PullUpConfig(){
    
    //Enabling Pull-Ups
    CNPU1bits.CN0PUE = 1; // pullup for CN0 (input RA4)
    CNPU1bits.CN1PUE = 1; // pullup for CN1 (input RB4)
    CNPU2bits.CN30PUE = 1; // pullup for CN30 (input RA2)
    
    return;
}
 
void timer2Config(){
    
    T2CONbits.TON = 1;
    T2CONbits.TSIDL = 0;
    T2CONbits.T32 = 0;
    T2CONbits.TCS = 0;
    
    return;
}


void timer2InterruptConfig(){
    
    //Interrupt Enable
    IEC0bits.T2IE = 1;
    
    return;
    
}
