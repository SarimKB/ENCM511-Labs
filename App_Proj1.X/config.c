/*
 * File:   config.c
 * Author: Sarim
 *
 * Created on October 29, 2021, 4:53 PM
 */


#include "xc.h"
#include "config.h"

void PullUpConfig(){
    
    //Enabling Pull-Ups
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE = 1;
    
    return;
}

void CN_Interrupt_Config(){
    
    //Priority
    IPC4bits.CNIP = 3;
    
    //Interrupt Enable
    IEC1bits.CNIE = 1;
    CNEN1bits.CN1IE = 1;
    CNEN1bits.CN0IE = 1;
    CNEN2bits.CN30IE = 1;
    
}


void timer2Config(){
    
    T2CONbits.TSIDL = 0;
    T2CONbits.T32 = 0;
    T2CONbits.TCS = 0;
    
    T2CONbits.TCKPS0 = 1;
    T2CONbits.TCKPS1 = 1;
    
    T2CONbits.TON = 1;
    
    return;
}


void timer2InterruptConfig(){
    
    //Setting priority
    IPC1bits.T2IP = 3;
    
    //Interrupt Enable
    IEC0bits.T2IE = 1;
    
    return;
    
}