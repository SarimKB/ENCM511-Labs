/*
 * File:   main.c
 * Author: Sarim
 *
 * Created on December 3, 2021, 7:34 PM
 */

//***Various files taken from previous work done this semester***

#pragma config FCKSM = CSECMD   // Clock switching is enabled, clock monitor disabled 
#pragma config OSCIOFNC = ON    //CLKO output disabled on pin 8, use as IO

#include "xc.h"
#include "ADC.h"
#include "UART2.h"
#include "config.h"
#include "timers.h"

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4


//------------- FUNCTIONS------------------

//Prototype for CN interrupt
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void);

// Prototype for display function
// 5 for voltage measurement
// 11 for resistance measurement
// 12 for capacitor measurement
// 10 for frequency measurement
void dispMultimeter(unsigned int component);


int main(void) {
    
    // MAIN WHILE LOOP
    while(1){
        Idle();
           
    }
    
    return 0;
}


// set controller interrupts for button subroutines
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void){
    
    // if CN interrupt flag is triggered
    if(IFS1bits.CNIF == 1){
        
        // if PB1 connected to RA2 is pressed
        // Measuring voltage
        if(PB1 == 0){
            
            
            
        }//END OF PB1
        
        // if PB2 connected to RA4 is pressed
        // Measuring resistance
        if(PB2 == 0){
            
            
        }//END OF PB2
        
        // if PB3 connected to RB4 is pressed
        // Measuring capacitance
        if(PB3 == 0){
            
               
        }// END OF PB3
        
    }//END OF MAIN IF
    
    // clearing the IF (CN interrupts) flag
    IFS1bits.CNIF = 0;
    
}


void dispMultimeter(unsigned int component){
    
    // Bring cursor to beginning and clear current text on screen
    Disp2String("\r\n");
    Disp2String("\e[1;1H\e[2J");
    
    // For voltage measurement
    if(component == 5){
        uint16_t volt = do_ADC;         //***EQUATION
        Disp2String("VOLTMETER Voltage = ");
        Disp2Dec(volt);
        Disp2String(" V");
    }
    
    // For resistance measurement
    if(component == 11){
        uint16_t resist = do_ADC;       //***EQUATION
        Disp2String("OHMETER Resistance = ");
        Disp2Dec(resist);
        Disp2String(" Ohm(s)");
    }
    
    // For capacitance measurement
    if(component == 12){
        uint16_t cap = do_ADC;          //***EQUATION
        Disp2String("Capacitance = ");
        Disp2Dec(cap);
        Disp2String(" uF");
    }
    
    // For frequency measurement *****SLIGHTLY DIFFERENT
    if(component == 10){
        uint16_t freq = do_ADC;         //***EQUATION
        Disp2String("Frequency = ");
        Disp2Dec(freq);
        Disp2String(" Hz");
    }
    
    return;
}
