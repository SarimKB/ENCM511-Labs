#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "displayer.h"
#include "UART2.h"
#include "timers.h"
#include <string.h>


//Displays current time on the terminal
void dispTimeTerm(unsigned int timeLeft_min, unsigned int timeLeft_sec){
    
    //Strings for formatting
    char min[3];
    char sec[3];
    
    Disp2String("\r");
    Disp2String("\e[1;1H\e[2J");
    
    sprintf(min, "%d", timeLeft_min);
    Disp2String(min);
    Disp2String("m : ");
    if(timeLeft_sec < 10){
        Disp2String("0");
        sprintf(sec, "%d", timeLeft_sec);
        Disp2String(sec);
        
    }
    else{
         sprintf(sec, "%d", timeLeft_sec);
         Disp2String(sec);
    }
    Disp2String("s");
    Disp2String("\r\n");
    
    return;
}
