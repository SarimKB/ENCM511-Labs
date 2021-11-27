/*
 * File:   interrupts.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 7:33 PM
 */


#include "xc.h"
#include "interrupts.h"
#include "timers.h"

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED_out LATBbits.LATB8

//Timer variables, global
unsigned int timeLeft_min = 0;
unsigned int timeLeft_sec = 0;

//Global variable for the time delay
uint16_t oneSecDelay = 16000;

//Variable keeping track of whether PB3 had a short or long press
unsigned int long_press = 0;

//Counter keeping track of seconds for PB3
int counter_pb = 0;

// set timer interrupts for timer 2 subroutine
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    // stopping the timer
    T2CONbits.TON = 0;
    
    // setting global flag to 1
    // TMR2Flag = 1;
    
    return;
}

// set controller interrupts for button subroutines
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void){
    
    if(IFS1bits.CNIF == 1){
        
        // check to see if buttons are pressed
        // if the button is pressed, set corresponding flag to 1
        // in other file, do the process, and when process is complete, set to 0?
        
        // if PB3 connected to RB4 is pressed
        // sort out whether long or short press is detected
        // act accordingly
        if(PB3 == 0){
            
            // start a 16 bit timer and if it hits 3 seconds, stop countdown and reset timer to 0
            // else, start countdown
            // set global flag to 1
            long_press = 0;
            while(PB3 == 0){
                counter_pb++;
                if(counter_pb > 3){
                    long_press = 1;
                }
                Delay_ms(oneSecDelay);
            }
            
            
            // see if timer is held down for 3 seconds, ie, TMR2 == PR2
            // if so, trigger the interrupt, which will be defined in the timer 2 subroutine above
            // in the interrupt, update the display to show 00:00
            // if the button is released within 3 seconds, start the countdown
            if(PORTBbits.RB4 == 1){
                
                if(long_press == 0){
                    
                }
                
                // start countdown
            }
            
        }
        
        // if PB2 connected to RA4 is pressed
        // set the seconds to be counted down. 
        // in increments of 1 second, increase seconds by 1 from 0 to 59
        // clear alarm message from terminal
        if(PB2 == 0){
            IFS0bits.T2IF = 0;
            // while button is pressed
            while(PB2 == 0){
                
                // check to see if time is at 59 minutes
                if(timeLeft_sec == 59)
                    break;
            
                //Incrementing minutes count by 1 minute
                timeLeft_sec += 1;


//                LED_out = 1;
//                Delay_ms(oneSecDelay);
//                LED_out = 0;
//                Delay_ms(oneSecDelay);
                //Time for user to see individual time change
                Delay_ms(oneSecDelay*2);
                
                //Displaying time to terminal
                dispTimeTerm(timeLeft_min, timeLeft_sec);
            
            }
            // set global flag to 1
            // maybe, if global flag == 1 clear terminal?
        }
        
        // if PB1 connected to RA2 is pressed
        // set the minutes to be counted down. 
        // in increments of 1 minute, increase minutes by 1 from 0 to 59
        // clear alarm message from terminal
        if(PB1 == 0){
            
            IFS0bits.T2IF = 0;
            // while button is pressed
            while(PB1 == 0){
                
                // check to see if time is at 59 minutes
                if(timeLeft_min == 59)
                    break;
            
                //Incrementing minutes count by 1 minute
                timeLeft_min += 1;

                

//                LED_out = 1;
//                Delay_ms(oneSecDelay);
//                LED_out = 0;
//                Delay_ms(oneSecDelay);
                //Time for user to see individual time change
                Delay_ms(oneSecDelay*2);
                
                //Displaying time to terminal
                dispTimeTerm(timeLeft_min, timeLeft_sec);
            
            }
            // set global flag to 1
            
        }
        
        
        
        
    }
    
    // clearing the IF flag
    IFS1bits.CNIF = 0;
    
}