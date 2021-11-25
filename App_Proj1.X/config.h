/*
 * File:   config.h
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:09 AM
 */


#include "xc.h"

//Enabling pull ups on inputs
void PullUpConfig();

//Enabling IO Change interrupt
void CN_Interrupt_Config();

//Configuring timer 2 register
void timer2RegConfig();

//Configuring timer 2 interrupt operation
void timer2InterruptConfig();