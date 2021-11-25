/*
 * File:   gpio.c
 * Author: Sarim
 *
 * Created on October 29, 2021, 4:53 PM
 */

#include "xc.h"
#include "gpio.h"

void IOinit(void){
    
    //Setting Inputs
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    //Setting Output
    TRISBbits.TRISB8 = 0;
    
    AD1PCFG = 0xFFFF;
    
    return;
}