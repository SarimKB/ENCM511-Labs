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

int main(void) {
    
    //Configuring inputs and output
    IOinit();
    
    //IO Checks
    IOcheck();
    
    //Enabling Pull Ups
    PullUpConfig();
    
    //Main program loop
    while(1){
        
        //Reset LED
        LED_out = 0;
        
        //If PB1 is pressed
        while(PB1 == 0){
            
            //If another PB is also pressed
            while( (PB2 == 0) || (PB3 == 0) ){
                LED_out = 1;  
            }
            LED_out = 0;
            
            //LED blinking at approx. 1 sec intervals
            LED_out = 1;
            Delay_ms(1000);
            LED_out = 0;
            Delay_ms(1000);
            
        }
        
        //If PB2 is pressed
        while(PB2 == 0){
            
            //If another PB is also pressed
            while( (PB1 == 0) || (PB3 == 0) ){
                LED_out = 1;  
            }
            LED_out = 0;
            
            //LED blinking at approx. 2 sec intervals
            LED_out = 1;
            Delay_ms(2000);
            LED_out = 0;
            Delay_ms(2000);
            
        }
        
        //If PB3 is pressed
        while(PB3 == 0){
            
            //If another PB is also pressed
            while( (PB2 == 0) || (PB1 == 0) ){
                LED_out = 1;  
            }
            LED_out = 0;
            
            //LED blinking at approx. 3 sec intervals
            LED_out = 1;
            Delay_ms(3000);
            LED_out = 0;
            Delay_ms(3000);
            
        }

    }
    
    return 0;
}
