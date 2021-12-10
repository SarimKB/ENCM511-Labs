/*
 * File:   main.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 6:45 PM
 */

//********Various source and header files taken from our previous projects this semester***************************

//Following code for config bits given from d2L

// FBS
#pragma config BWRP = OFF               // Table Write Protect Boot (Boot segment may be written)
#pragma config BSS = OFF                // Boot segment Protect (No boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Code Flash Write Protection bit (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Flash Code Protection bit (No protection)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (WDT prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable bit (WDT enabled)

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = OFF              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
#pragma config RTCOSC = SOSC            // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = OFF             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

#include "xc.h"
#include "UART2.h"
#include "config.h"
#include "gpio.h"
#include "timers.h"
#include "interrupts.h"
#include "ADC.h"
#include "CTMU.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//Setting up the buttons, and LED. Mapping to respective IOs as defined in app project document
#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED_out LATBbits.LATB8

//------------- FUNCTIONS------------------

//Prototype for CN interrupt
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void);

// Prototype for display function
// 5 for voltage measurement
// 11 for resistance measurement (PIN 16)
// 12 for capacitor measurement  (PIN 15)
// 10 for frequency measurement  (PIN 17)
void dispMultimeter(unsigned int component);

int main(void) {

    
    //Configuring inputs and output
    IOinit();
    
    //Initialize and configure CN interrupts
    CN_Interrupt_Config();
    
    //Initialize pullups for all inputs
    PullUpConfig();
    
//    //Configuring timer 2 register
//    timer2RegConfig();
//
//    //Configuring timer 2 interrupt operation
//    timer2InterruptConfig();
    
    //main while loop
    while(1){
            
        
    }
    
    return 0;
}

void dispMultimeter(unsigned int component){
    
    // Bring cursor to beginning and clear current text on screen
    Disp2String("\r\n");
    Disp2String("\e[1;1H\e[2J");
    
    //uint16_t Vdd = 3.25;
    
    // For voltage measurement
    if(component == 5){
        uint16_t volt_in = do_ADC(component);
        double Vdd = 3.25;
        double Vmax = 1023;
        double volt = ( ( (double)volt_in)/Vmax )*Vdd;
        char daString[60];
        sprintf(daString, "%.2f", volt);
        
        Disp2String("VOLTMETER Voltage = ");
        Disp2String(daString);
        Disp2String(" V");
    }
    
    // For resistance measurement
    if(component == 11){
        uint16_t Vanalog = do_ADC(component);
        double Vdd = 3.25;
        double Vmax = 1023;
        double R1k = 1000;
        double volt = ( ( (double)Vanalog)/Vmax )*Vdd;
        char daString[60];
        double resist = (volt * R1k) / (Vdd - volt);
        int resist_int = resist;
        
        

        //sprintf(daString, "%d", resist_int);
        sprintf(daString, "%.2f", volt);

        Disp2String("OHMETER Resistance = ");
        Disp2Dec(resist_int);
        //Disp2String(daString);
        Disp2String(" Ohm(s)");
    }
    
    // For capacitance measurement
    if(component == 12){
        uint16_t ctmu_in = CTMU();
        double Vdd = 3.25;
        double Vmax = 1023;
        double Vcap = ( ( (double)ctmu_in)/Vmax )*Vdd; // capacitor voltage
        double microdelay = 71.42; // approximate delay value used to charge capacitor, in us
        double microamps = 0.55; // approximate amps 
        double capacitance = (71.42 * 0.55) / ctmu_in;
        
        char daString[60];
        sprintf(daString, "%.20f", capacitance);
        
        Disp2String("Capacitance = ");

        Disp2String(daString);
        Disp2String(" uF");
    }
    
    // For frequency measurement *****SLIGHTLY DIFFERENT
    if(component == 10){
        uint16_t freq = do_ADC(component);         //***EQUATION    //THIS AINT IT CHIEF
        Disp2String("Frequency = ");
        Disp2Dec(freq);
        Disp2String(" Hz");
    }
    
    return;
}

// set controller interrupts for button subroutines
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void){
    
    // if CN interrupt flag is triggered
    if(IFS1bits.CNIF == 1){
        
        // if PB3 connected to RB4 is pressed
        // Capacitance Measurement
        if(PB3 == 0){
            
          dispMultimeter(12);
            
        }// END OF PB3
        
        
        // if PB2 connected to RA4 is pressed
        // Resistance Measurement
        if(PB2 == 0){
            
            dispMultimeter(11);
            
            
        }//END OF PB2
        
        
        // if PB1 connected to RA2 is pressed
        // Voltage Measurement
        if(PB1 == 0){
            
            dispMultimeter(5);
            
        }//END OF PB1
        
    }//END OF MAIN IF
    
    // clearing the IF (CN interrupts) flag)
    IFS1bits.CNIF = 0;
    
}




