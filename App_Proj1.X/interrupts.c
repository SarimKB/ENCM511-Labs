/*
 * File:   interrupts.c
 * Author: Sarim
 *
 * Created on November 24, 2021, 7:33 PM
 */


#include "xc.h"
#include "interrupts.h"
#include "timers.h"
#include "ChangeClk.h"
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
volatile int CD_start = 0;

// set timer interrupts for timer 2 subroutine
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    
    //Clearing timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    
    // stopping the timer
    T2CONbits.TON = 0;
    
    return;
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
                
                // To start or pause countdown
                if(long_press == 0){
                    CD_start = !CD_start;
                }
                // To reset countdown
                else{
                    CD_start = 0;
                    timeLeft_min = 0;
                    timeLeft_sec = 0;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                }
                
            }// END OF PB3 == 1
            
            
            // MAIN COUNTDOWN LOOP
            while(CD_start = 1){

                if(timeLeft_sec != 0){
                    timeLeft_sec -= 1;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                    LED_out = 1;
                }
                else if(timeLeft_min != 0){
                    timeLeft_min -= 1;
                    timeLeft_sec = 59;
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                    LED_out = 1;
                }
                else{
                    dispTimeTerm(timeLeft_min, timeLeft_sec);
                    Disp2String(" -- ALARM");
                    CD_start = 0;
                    break;
                }

                //One Second Delay
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
                LED_out = 0;
            
            }// END OF WHILE COUNTDOWN
            LED_out = 1;
            
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