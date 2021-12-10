/*
 * File:   ADC.h
 * Author: Sarim
 *
 * Created on November 21, 2021, 5:18 PM
 */
#include "xc.h"
//Function to perform the ADC sampling for a specific analog input pin
uint16_t do_ADC(unsigned int input);

//ADC ISR
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);