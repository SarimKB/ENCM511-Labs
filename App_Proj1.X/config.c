/*
 * File:   config.c
 * Author: Sarim
 *
 * Created on October 29, 2021, 4:53 PM
 */


#include "xc.h"
#include "config.h"
// this file configures pull up and pull down

void PullUpConfig(){
    
    //Enabling Pull-Ups
    CNPU1bits.CN0PUE = 1; // pullup for CN0 (input RA4)
    CNPU1bits.CN1PUE = 1; // pullup for CN1 (input RB4)
    CNPU2bits.CN30PUE = 1; // pullup for CN30 (input RA2)
    
    return;
}

void CN_Interrupt_Config(){
    
    //Priority?????
    IPC4bits.CNIP = 6;  // set to highest priority
    //Interrupt request enable
    IEC1bits.CNIE = 1;
    //Enable CN Input for every single button
    CNEN1bits.CN1IE = 1; // RB4
    CNEN1bits.CN0IE = 1; //RA4
    CNEN2bits.CN30IE = 1; // RA2
    
    return;
    
}


void timer2Config(){
    
    
    T2CONbits.TSIDL = 0; // make program continue when idle
    T2CONbits.T32 = 0; // do not use 32 bit timer use 16 bit instead
    T2CONbits.TCS = 0; // use internal clk
    
    T2CONbits.TCKPS0 = 1; // ?
    T2CONbits.TCKPS1 = 1; // ?
    
    T2CONbits.TON = 1; // turn on the CLK
    
    return;
}


void timer2InterruptConfig(){
    
    //Setting priority
    IPC1bits.T2IP = 7;
    
    //Interrupt Enable
    IEC0bits.T2IE = 1;
    
    return;
    
}


 