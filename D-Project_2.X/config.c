/*
 * File:   config.c
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:07 AM
 */


#include "xc.h"
#include "config.h"

void PullUpConfig(){
    
    //Enabling Pull-Ups
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE - 1;
    
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
    
    //Setting priority
    
    
    //Interrupt Enable
    IEC0bits.T2IE = 1;
    
    
    
}