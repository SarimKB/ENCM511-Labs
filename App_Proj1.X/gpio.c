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
    TRISAbits.TRISA2 = 1;  // Set RA2 as input
    TRISAbits.TRISA4 = 1;  // Set RA4 as input
    TRISBbits.TRISB4 = 1;  // Set RB4 as input
    
    //Setting Output (LED))
    TRISBbits.TRISB8 = 0;  // Set RB8 as output
    
    AD1PCFG = 0xFFFF; // ????
    
    return;
}