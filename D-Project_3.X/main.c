/*
 * File:   main.c
 * Author: Sarim
 *
 * Created on October 29, 2021, 4:52 PM
 */

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
#include "timers.h"
#include "clocks.h"
#include "gpio.h"
#include "config.h"
#include "UART2.h"

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED_out LATBbits.LATB8

//Global variable for the time delay
uint16_t timeDelay = 8000;

int main(void) {
    
    //Configuring inputs and output
    IOinit();
    
    //Enabling Pull Ups
    PullUpConfig();
    
    LED_out = 0;
    //Main program loop
    while(1){
        //Reset LED
        LED_out = 0;
        
        //LED should remain off if no button is pressed
        while(PB1 == 1 && PB2 == 1 && PB3 == 1){
            LED_out = 0;
            Disp2String("\n\r Nothing pressed");
        }
        
        //If PB1 is pressed
        while(PB1 == 0){
            
            //Printing to console
            Disp2String("\n\r PB1 is pressed");
            
           //If another PB is also pressed
           while( (PB2 == 0) || (PB3 == 0) ){
                LED_out = 1;  
                
                //Printing depending on which other PBs are also pressed
                if(PB3 == 1){
                    Disp2String("\n\r PB1 and PB2 are pressed");
                }
                else if(PB2 == 1){
                    Disp2String("\n\r PB1 and PB3 are pressed");
                }
                else{
                    Disp2String("\n\r All PBs pressed");
                }
            }
            LED_out = 0;
            
            //LED blinking at approx. 0.5 sec intervals
            timeDelay = 4000;
            LED_out = 1;
            Delay_ms(timeDelay);
            LED_out = 0;
            Delay_ms(timeDelay);
            
        }
        
        //If PB2 is pressed
        while(PB2 == 0){
            
            //Printing to console
            Disp2String("\n\r PB2 is pressed");
            
            //If another PB is also pressed
            while( (PB1 == 0) || (PB3 == 0) ){
                LED_out = 1;
                
                //Printing depending on which other PBs are also pressed
                if(PB3 == 1){
                    Disp2String("\n\r PB1 and PB2 are pressed");
                }
                else if(PB1 == 1){
                    Disp2String("\n\r PB2 and PB3 are pressed");
                }
                else{
                    Disp2String("\n\r All PBs pressed");
                }
                
            }
            LED_out = 0;
            
            //LED blinking at approx. 2 sec intervals
            timeDelay = 16000;
            LED_out = 1;
            Delay_ms(timeDelay);
            LED_out = 0;
            Delay_ms(timeDelay);
            
        }
        
        //If PB3 is pressed
        while(PB3 == 0){
            
            //Printing to console
            Disp2String("\n\r PB3 is pressed");
            
            //If another PB is also pressed
            while( (PB2 == 0) || (PB1 == 0) ){
                LED_out = 1;  
                
                //Printing depending on which other PBs are also pressed
                if(PB2 == 1){
                    Disp2String("\n\r PB1 and PB3 are pressed");
                }
                else if(PB1 == 1){
                    Disp2String("\n\r PB2 and PB3 are pressed");
                }
                else{
                    Disp2String("\n\r All PBs pressed");
                }
            }
            LED_out = 0;
            
            //LED blinking at approx. 3 sec intervals
            timeDelay = 24000;
            LED_out = 1;
            Delay_ms(timeDelay);
            LED_out = 0;
            Delay_ms(timeDelay);
            
        }

    }
    
    return 0;
}