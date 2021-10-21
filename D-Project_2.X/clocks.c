/*
 * File:   clocks.c
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:08 AM
 */

//This code is given from d2L under "Driver Topic 2 : HW IO Control and Timers"
#include "xc.h"
#include "clocks.h"

//clkval = 8 for 8MHz; 
//clkval = 500 for 500kHz; 
//clkval = 32 for 32kHz; 
void NewClk(unsigned int clkval)  
{
    char COSCNOSC;
    if (clkval == 8)  //8MHz
    {
        COSCNOSC = 0x00;
    }
    else if (clkval == 500) // 500 kHz
    {
        COSCNOSC = 0x66;
    }
    else if (clkval== 32) //32 kHz
    {
        COSCNOSC = 0x55; 
    }
    else // default 32 kHz
    {
        COSCNOSC = 0x55;
    }
        // Switch clock to 500 kHz
     SRbits.IPL = 7;  //Disable interrupts
     CLKDIVbits.RCDIV = 0;  // CLK division = 0
     __builtin_write_OSCCONH(COSCNOSC);   // (0x00) for 8MHz; (0x66) for 500kHz; (0x55) for 32kHz;
     __builtin_write_OSCCONL(0x01);
     OSCCONbits.OSWEN=1;
     while(OSCCONbits.OSWEN==1)
     {} 
     SRbits.IPL = 0;  //enable interrupts
}

