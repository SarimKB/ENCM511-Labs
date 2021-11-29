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

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED_out LATBbits.LATB8

//Global variable for the time delay
//uint16_t oneSecDelay = 8000;

// user defined global variable used as a flag
int CN1flag = 0;
int CN0flag = 0;
int CN30flag = 0;

//Timer variables, global
//unsigned int timeLeft_min = 0;
//unsigned int timeLeft_sec = 0;

int main(void) {
    //NewClk(32);
    //Configuring inputs and output
    IOinit();
    
    //Initialize CN interrupts, and configure
    CN_Interrupt_Config();
    
    //Initialize pullups for inputs
    PullUpConfig();
    
    
  /*
    while(1){
       
         
        //Reset LED
        //LED_out = 0;

        //When PB1 is pressed. Incrementing minutes count
        while(PB1 == 0){
            
            // check to see if time is at 59 minutes
            if(timeLeft_min == 59)
                break;
            
            //Incrementing minutes count by 1 minute
            timeLeft_min += 1;

            //Time for user to see individual time change
            int x;
            for(x = 0; x < 1000; x++){               
                Delay_ms(oneSecDelay);
            }
            
            //Displaying time to terminal
            dispTimeTerm(timeLeft_min, timeLeft_sec);
            
        }
        
        //When PB2 is pressed. Incrementing seconds count
        while(PB2 == 0){
            
            // check to see if time is at 59 minutes
                if(timeLeft_sec == 59)
                    break;
            
                //Incrementing minutes count by 1 minute
                timeLeft_min += 1;

                
//                LED_out = 1;
//                Delay_ms(oneSecDelay);
//                LED_out = 0;
//                Delay_ms(oneSecDelay);
                //Time for user to see individual time change
                int x;
                for(x = 0; x < 1000; x++){               
                    Delay_ms(oneSecDelay);
                }
                
                //Displaying time to terminal
                dispTimeTerm(timeLeft_min, timeLeft_sec);
            
        }
             
    }
    
//    while(1){
//        // loop to run idle / sleep mode
//        Idle();
////        uint16_t delay = 16000;
////        LED_out = 1;
////        Delay_ms(delay);
////        LED_out = 0;
////        Delay_ms(delay);
//    }
         */
    while(1){
        Idle();
    }
    
   
    return 0;
}



