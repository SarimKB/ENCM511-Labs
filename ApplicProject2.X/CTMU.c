#include "xc.h"
#include "CTMU.h"
#include "timers.h"
#include "UART2.h"

// TAKEN FROM D2L
void setup(void){
    
    //CTMUCON - CTMU Control register
     
    CTMUCON = 0x0000; //make sure CTMU is disabled
    CTMUCONbits.CTMUEN = 0;
    CTMUCONbits.TGEN = 1;
    CTMUCONbits.EDG1POL = 1;
    CTMUCONbits.EDG2POL = 1;
    
    CTMUCONbits.EDG1SEL = 0b10;
    CTMUCONbits.EDGSEQEN = 1;
    CTMUCONbits.EDGEN = 1;
    CTMUCONbits.EDG1STAT = 0;
   
    // CTMU continues to run when emulator is stopped,CTMU continues
    // to run in Idle mode, Time Generation mode enabled, Edges are
    // blocked. No edge sequence order, Analog current source not
    // grounded, trigger output disabled, Edge2 polarity = positive level,
    // Edge2 source = source 0, Edge1 polarity = positive level,
    // Edge1 source = source 0, Set Edge status bits to zero
    //CTMUICON - CTMU Current Control Register
    CTMUICON = 0x0000; 
    CTMUICONbits.IRNG0 = 1; //.55uA, Nominal - No Adjustment
    CTMUICONbits.IRNG1 = 0; //.55uA, Nominal - No Adjustment
    /**************************************************************************/
    /* Set up AD Converter ****************************************************/
    /**************************************************************************/
    
    
    AD1CON1bits.ADON=0;            //Turn off ADC, turn on before sampling in do_ADC()
    AD1CON1bits.ADSIDL=0;        //Continue ADC operation in idle mode
    AD1CON1bits.FORM=0b00;        //0b00: Int, 01: Signed Int, 10:Fractional, 11:Signed Fract
    AD1CON1bits.SSRC=0b000;    //Start ADC conversion Time set by SAMC has passed
    AD1CON1bits.ASAM=0;     //Next Sampling begins when SAMP bit is set
    AD1CON1bits.SAMP=0;        //Set this bit in ADC routine to start sampling  

    // Sampling time and ADC Clk select
    AD1CON2bits.VCFG=0b000;     //Vref+=AVDD   Vref-=AVSS
    AD1CON2bits.CSCNA=0;    //Do not scan inputs; use channel selected by CH0SA bits
    AD1CON2bits.SMPI=0b0000; //Any ADC interrrups occur at completion of each sample/convert seq.
    AD1CON2bits.BUFM=0; //Buffer confugured as 1 16 word buffer 
    AD1CON2bits.ALTS=0; //Always use MUXA input MUX settings
    AD1CON3bits.ADRC=0; //0: Use System clk; 1: ADC uses internal RC clock for idle or sleep mode
    AD1CON3bits.SAMC=0; 
    AD1CON3bits.ADCS=0; //ADCS conversion clock select bits. Ignored if using internal AD RC clock. 
    
    // MUX settings
    AD1CHSbits.CH0NA = 0;    //Ch0 -ve Input is VR-
    AD1CHSbits.CH0SA = 12;    //YOUR ADC CHANNEL HERE
   
    //IO port selection
    TRISBbits.TRISB12 = 1;  //SET YOUR PIN AS AN INPUT
    AD1PCFGbits.PCFG12 = 0;     //SET YOUR PIN AS AN ANALOG INPUT
    AD1CON1bits.ADON=1;
    
}

// TAKEN FROM D2L
uint16_t CTMU(void){
    
    //Clearing TMR2 and resetting flag
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    
    timer2Config();
    
    int i;
    int j = 0; //index for loop
    uint16_t Vread = 0;
    uint16_t Vavg = 0;
    double VTot = 0;
    //assume CTMU and A/D have been setup correctly
    setup();
    CTMUCONbits.CTMUEN = 1;//Enable the CTMU
    
    CTMUICONbits.IRNG = 0b01;
    
    CTMUICONbits.ITRIM = 0;
    
//    for(i = 0; i < 1; i++)
//    {
        AD1CON1bits.SAMP = 1;  //Manual sampling start - move to after IDISSEN=0 if long time delay
        CTMUCONbits.IDISSEN = 1; //drain charge on the circuit
       

        //[   TIME DELAY HERE   ]
        // time delay for about 14 microseconds
        int a = 0;
        int time = 10000;
//        for(a = 0; a < 30000; a++) Delay_ms(1);
//        for(a = 0; a < 30000; a++) Delay_ms(1);
//        for(a = 0; a < 10000; a++) Delay_ms(1);
//        Disp2String("TEST 1 SECOND CAP");
        for(a = 0; a < 10000; a++) Delay_ms(1);
        CTMUCONbits.IDISSEN = 0; //end drain of circuit
        
        CTMUCONbits.EDG1STAT = 1; //Begin charging the circuit
        //using CTMU current source
        for(a = 0; a < 5; a++) Delay_ms(1);      // delay by about 71 us 

        //[     TIME DELAY HERE    ]
//        for(a = 0; a < 30000; a++) Delay_ms(1);
//        for(a = 0; a < 30000; a++) Delay_ms(1);
//        for(a = 0; a < 10000; a++) Delay_ms(1);
//        Disp2String("TEST 2 SECOND CAP");
        
        
        CTMUCONbits.EDG1STAT = 0; //Stop charging circuit
        IFS0bits.AD1IF = 0; //make sure A/D Int not set
        AD1CON1bits.SAMP = 0; //and begin A/D conv.
        while(!AD1CON1bits.DONE); //Wait for A/D convert complete
        Vread = ADC1BUF0; //Get the value from the A/D
        IFS0bits.AD1IF = 0; //Clear A/D Interrupt Flag
        VTot += Vread; //Add the reading to the total
       
//    }
    //If you are using multiple loops, don't forget to divide to average
    Vavg = ((double)VTot/1); //1 Measurement
    
    char daString[60];
        
        sprintf(daString, "%.2f", VTot);
        Disp2String(daString);
//    Disp2Dec(Vavg);
//    XmitUART2('\n', 1);
//    XmitUART2('\r', 1);
    VTot = 0;
    
    CTMUCONbits.CTMUEN = 0;
    
    T2CONbits.TON = 0;
    
    
    
    return Vavg;
    
    
}
