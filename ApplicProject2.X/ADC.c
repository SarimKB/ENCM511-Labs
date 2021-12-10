/*
 * File:   ADC.c
 * Author: Sarim
 *
 * Created on November 21, 2021, 5:22 PM
 */

#include "xc.h"
#include "ADC.h"

//FOLLOWING FUNCTION do_ADC AS SHOWN IN LECTURE SLIDES ON D2L
// With a slight adjustment from the previous project

uint16_t do_ADC(unsigned int input){
   
    uint16_t ADCValue;
    
    //------------ADC Initialization-----------------
    
    AD1CON1bits.ADON = 1;       //Turn on ADC module
    
    AD1CON1bits.FORM = 0b00;    //Format bits
    AD1CON1bits.SSRC = 0b111;   //Internal counter ends sampling
    AD1CON1bits.ASAM = 0;       //Sampling to begin when SAMP bit is set
    
    AD1CON2bits.VCFG = 0b000;   //Voltage ref config
    AD1CON2bits.CSCNA = 0;      //Scan input selection
    AD1CON2bits.SMPI = 0b0000;
    AD1CON2bits.BUFM = 0;       //Buffer mode select
    AD1CON2bits.ALTS = 0;       //Using MUX A input settings
    
    AD1CON3bits.ADRC = 0;       //Using system clock
    AD1CON3bits.SAMC = 0b11111; //Sample time
    AD1CON3bits.ADCS = 0b11111;
    
    AD1CHSbits.CH0NA = 0;       //Negative input
    AD1CHSbits.CH0SA = input;       //Positive input (Depending on input variable)
    
    AD1PCFGbits.PCFG12 = 0;     //Analog mode for AN12
    AD1PCFGbits.PCFG11 = 0;     //Analog mode for AN11
    AD1PCFGbits.PCFG10 = 0;     //Analog mode for AN10
    AD1PCFGbits.PCFG5 = 0;      //Analog mode for AN5
    
    AD1CSSLbits.CSSL5 = 0;
    
    //---------ADC SAMPLING AND CONVERSION-------------------
    
    AD1CON1bits.SAMP = 1;       //Start sampling
    while(AD1CON1bits.DONE == 0){
        
    }
    ADCValue = ADC1BUF0;        //Storing ADC output
    AD1CON1bits.SAMP = 0;       //Stop sampling
    AD1CON1bits.ADON = 0;       //Turn off ADC module

    return ADCValue;
}