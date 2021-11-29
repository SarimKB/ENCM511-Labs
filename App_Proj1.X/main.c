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
#include "displayer.h"
#include <stdbool.h>

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED_out LATBbits.LATB8

//Timer variables, global
unsigned int timeLeft_min = 0;
unsigned int timeLeft_sec = 0;

//Global variable for the time delay
uint16_t oneSecDelay = 8000;

//Variable keeping track of whether PB3 had a short or long press
unsigned int long_press = 0;

//Counter keeping track of seconds for PB3
int counter_pb = 0;

//Variable keeping track of the countdown start or pause
//0 -> paused
//1 -> start
bool CD_start = 0;

//Boolean to toggle LED status
volatile bool led_toggle = 0;

int main(void) {
    //NewClk(32);
    //Configuring inputs and output
    IOinit();
    
    //Initialize CN interrupts, and configure
    CN_Interrupt_Config();
    
    //Initialize pullups for inputs
    PullUpConfig();
    
    while(1){
        
            while(!CD_start){
                Idle();
            }
        
            // MAIN COUNTDOWN LOOP
            while(CD_start){
                
                led_toggle = !led_toggle;
                if(timeLeft_sec != 0){
                    timeLeft_sec -= 1;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                }
                else if(timeLeft_min != 0){

                    timeLeft_min -= 1;
                    timeLeft_sec = 59;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                }
                else{
                    LED_out = 1;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                    Disp2String(" -- ALARM");
                    CD_start = 0;
                    break;
                }
                
                // LED ON
                if(led_toggle){
                    LED_out = 1;
                }
                // LED OFF
                else{
                    LED_out = 0;
                }
                Delay_ms(oneSecDelay*2);

            
            }// END OF WHILE COUNTDOWN
        
    }
    
    return 0;
}


// set controller interrupts for button subroutines
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void){
    
    if(IFS1bits.CNIF == 1){
        
        // if PB3 connected to RB4 is pressed
        // sort out whether long or short press is detected
        // act accordingly
        if(PB3 == 0){
            
            // start a 16 bit timer and if it hits 3 seconds, stop countdown and reset timer to 0
            // else, start countdown
            // set global flag to 1
            long_press = 0;
            counter_pb = 0;
            while(PB3 == 0){
                counter_pb++;
                if(counter_pb > 3){
                    long_press = 1;
                }
                
                int s;
                for(s = 0; s < 30000; s++){   
                    
                    Delay_ms(oneSecDelay);
                }
                for(s = 0; s < 30000; s++){   
                    
                    Delay_ms(oneSecDelay);
                }
                for(s = 0; s < 10000; s++){   
                    
                    Delay_ms(oneSecDelay);
                }   
            }
                
            // see if timer is held down for 3 seconds
            // in the interrupt, update the display to show 00:00
            // if the button is released within 3 seconds, start the countdown
            if(PB3 == 1){
                
                // If short press
                // To start or pause countdown
                if(long_press == 0){
                    CD_start = !CD_start;
                }
                // If long press
                // To reset countdown
                else{
                    LED_out = 0;
                    CD_start = 0;
                    timeLeft_min = 0;
                    timeLeft_sec = 0;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                }
                
            }// END OF PB3 == 1
               
        }// END OF PB3
        
        
        // if PB2 connected to RA4 is pressed
        // set the seconds to be counted down. 
        // in increments of 1 second, increase seconds by 1 from 0 to 59
        // clear alarm message from terminal
        if(PB2 == 0){
            
            // while button is pressed
            while(PB2 == 0){
                int z;
                for(z = 0; z < 30000; z++){   
                    
                    Delay_ms(oneSecDelay);
                }
                for(z = 0; z < 10000; z++){   
                    
                    Delay_ms(oneSecDelay);
                }
                // check to see if time is at 59 minutes
                if(timeLeft_sec == 59)
                    break;
            
                //Incrementing minutes count by 1 minute
                timeLeft_sec += 1;
                
                //Displaying time to terminal
                dispTimeTerm(timeLeft_min, timeLeft_sec);
            
            }// END OF WHILE
            
        }//END OF PB2
        
        
        // if PB1 connected to RA2 is pressed
        // set the minutes to be counted down. 
        // in increments of 1 minute, increase minutes by 1 from 0 to 59
        // clear alarm message from terminal
        if(PB1 == 0){
            
            // while button is pressed
            while(PB1 == 0){
                
               int w;
               for(w = 0; w < 30000; w++){   
                    
                Delay_ms(oneSecDelay);
               }
               for(w = 0; w < 10000; w++){   
                    
                Delay_ms(oneSecDelay);
               }
                
               // check to see if time is at 59 minutes
               if(timeLeft_min == 59)
                   break;
            
               //Incrementing minutes count by 1 minute
               timeLeft_min += 1;
                
               //Displaying time to terminal
               dispTimeTerm(timeLeft_min, timeLeft_sec);
            
            }
            
        }//END OF PB1
        
    }//END OF MAIN IF
    
    // clearing the IF flag
    IFS1bits.CNIF = 0;
    
}




