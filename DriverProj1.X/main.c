/*
 * File:   main.c
 * Author: Sarim Kamran
 *
 * Created on September 29, 2021, 8:57 PM
 */


#include "xc.h"

int main(void) {
    
    //Initializing inputs and outputs
    
    TRISA = 0x00FF;     //Configuring bits as inputs
    TRISB = 0x0000;     //Configuring bits as outputs
    
    while(1){
        //UCID IS 30069623
        
        //Display Nothing
        if(PORTA == 0x0000){
            LATB = 0x0000;
        }
        
        //Display first number of UCID
        else if(PORTA == 0x0001){
            LATB = 0X0007;
        }
        
        //Display second number of UCID
        else if(PORTA == 0x0002){
            LATB = 0X0000;
        }
        
        //Display third number of UCID
        else if(PORTA == 0x0003){
            LATB = 0X0000;
        }
        
        //Display fourth number of UCID
        else if(PORTA  == 0x0004){
            LATB = 0X0197;
        }
        
        //Display fifth number of UCID
       else if(PORTA  == 0x0005){
            LATB = 0X3397;
        }
        
        //Display sixth number of UCID
        else if(PORTA  == 0x0006){
            LATB = 0X0197;
        }
        
        //Display seventh number of UCID
        else if(PORTA == 0x0007){
            LATB = 0X0003;
        }
        
        //Display eighth number of UCID
        else if(PORTA == 0x0040){
            LATB = 0X0007;
        }
        
        //Display Nothing
        else{
            LATB = 0x0000;
        }
        
    }
    
    
    return 0;
}
