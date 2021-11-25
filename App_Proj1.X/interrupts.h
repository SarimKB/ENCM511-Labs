/*
 * File:   interrupts.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 7:33 PM
 */

#include "xc.h"

//Timer 2 ISR
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void);

//IO Change ISR
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void);