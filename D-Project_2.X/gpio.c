/*
 * File:   gpio.c
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:08 AM
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
    
    return;
}

void IOcheck(void){
    
    
    
    return;
}