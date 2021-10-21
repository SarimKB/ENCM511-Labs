/*
 * File:   main.c
 * Author: Sarim
 *
 * Created on October 12, 2021, 1:06 AM
 */


#include "xc.h"
#include "timers.h"
#include "clocks.h"
#include "gpio.h"
#include "config.h"

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
        }
        
        //If PB1 is pressed
        while(PB1 == 0){
            
           //If another PB is also pressed
           while( (PB2 == 0) || (PB3 == 0) ){
                LED_out = 1;  
            }
            LED_out = 0;
            
            //LED blinking at approx. 1 sec intervals
            timeDelay = 8000;
            LED_out = 1;
            Delay_ms(timeDelay);
            LED_out = 0;
            Delay_ms(timeDelay);
            
        }
        
        //If PB2 is pressed
        while(PB2 == 0){
            
            //If another PB is also pressed
            while( (PB1 == 0) || (PB3 == 0) ){
                LED_out = 1;  
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
            
            //If another PB is also pressed
            while( (PB2 == 0) || (PB1 == 0) ){
                LED_out = 1;  
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
