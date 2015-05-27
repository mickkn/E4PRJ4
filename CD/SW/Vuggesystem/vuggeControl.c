/* ========================================
 *
 * Copyright Baby Watch, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Baby Watch.
 *
 * ========================================
*/
//========================================================================
// FILENAME : vuggeControl.c
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : c file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of vuggeControl.c
// 0.2	17-04-2015 - Jeppe - I2C to Controller implemented, needstesting
// 0.3	30-04-2015 - Jeppe - I2C tweeked and tested
// 0.4	23-05-2015 - Jeppe - Main implemented with loop and initiation
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - I2C needs testing, regulering needs finished implementation, sensorFortolker needs finished implementation
// 0.3 - Regulering needs finished implementation, sensorFortolker needs finished implementation
// 0.4 - Shutdown needs properhandling
//========================================================================

// Includes
#include <project.h>
#include <stdio.h>
#include <cytypes.h>
#include "fixedMath.h"
#include "i2cKommunikation.h"
#include "sensorFortolker.h"
#include "regulering.h"

// Attributes
int* endstopStatusPtr_;
int* reguleringsStatusPtr_;
uint8* i2cPtr_;
BOOL ready = FALSE;

// Prototype functions
void initVuggesystem();
void reguleringsStatus(void);
void lukSystem(void);
void checkOn_Off(void);
void checkEndstop();
void error(char* str);
CY_ISR_PROTO(loopIsr);


int main()
{
    CyDelay(500);
    CyGlobalIntEnable;
    initVuggesystem();
     // Global interrupts
    debugOut_PutString("\r\n\nWelcome to Baby Watch Vuggesystem\r\n\n");
    
    fix16_t count = 0;
    while(TRUE)
    {
        /* wait for the remainder of the loop period while  *
         * exposing the idle period on the activity debug   *
         * pin.                                             */
        CyPins_ClearPin(activityDebug_0);  
        while(!ready);
        CyPins_SetPin(activityDebug_0);
        
        //check system status
        checkEndstop();
        checkOn_Off();
        //update the target parameters
        updateRegParameter(i2cPtr_[I2C_FREK_REG], i2cPtr_[I2C_VINK_REG]);
        //calculate correction from sensor input
        fix16_t angle = getVuggeUdsvingSens();
        fix16_t C = beregnRegulering(angle);
        
        //opdater motor output
        PWMStyring(C);
        //check for successful control output
        reguleringsStatus();
//        print1 = count;
//        count += 3277;
        
        /* ***** DEBUG ***** */
//        char str[30];
//        sprintf(str, "%d, ", angle>>);
//        debugOut_PutString(str);
//        
//        sprintf(str, "%d; ", print2>>15);
//        debugOut_PutString(str);
        /* *** DEBUG END *** */
        
        //set waiting flag to false
        ready = FALSE;
    }
}

void initVuggesystem()
{   
    debugOut_Start();
        
    //Start components
    loopTimer_Start();
    loop_isr_StartEx(loopIsr);
    
    //start sensors
    initSensors(); 
    
    //start controller I2C connection
    initI2C();
    i2cPtr_ = sendConKom();
    
    //start regulering
    initRegulering();
    reguleringsStatusPtr_ = getReguleringsStatus();
}


/* Function Name: reguleringsStatus
   Summary:
    Checks for error and sets the I2CTxReg[1] with regStatus error message. ERR = 0b10000000(128_dec 80_hex) , STALL 0b11000000(192_dec C0_hex)
*/
void reguleringsStatus()
{
    int reguleringsStatus = *reguleringsStatusPtr_;
    if(reguleringsStatus > 1)
    {  
        i2cPtr_[4] = reguleringsStatus;
        lukSystem();
    }
    
}

/* Function Name: lukSystem
   Summary:
   Stops and closes all motor control operation  
*/
void lukSystem()
{  
        loop_isr_Stop();
        char str[30];
        sprintf(str, "\r\n\n\n SHUTDOWN AKTIVERET \r\n\n\n");
        debugOut_PutString(str);
        
        i2cPtr_[4] = 0b10010000;
        i2cPtr_[I2C_FREK_REG] = 0;
        i2cPtr_[I2C_VINK_REG] = 0;
        PWM_Stop();
        CyPins_ClearPin(PWM_A_0);
        CyPins_ClearPin(PWM_B_0);
        while(1){}
}

/* Function Name: checkOn_Off
   Summary:
   Checks i2cBuffer reg 4 for shutdown indicator 0x0f and signals Ready for shutdown 
*/
void checkOn_Off()
{  
    uint8 shutdown = i2cPtr_[1];
    if(shutdown == 0x0f)
    {  
        // Set some pin LOW to shutdown motorcircuit??
        char str[30];
        sprintf(str, "\r\n\n\n Contoller lukker vuggesystemet \r\n\n\n");
        debugOut_PutString(str);
        
        
        lukSystem();
        
    }
}

/* Function Name: checkEndstop
   Summary:
    Checks enstopstatus. If TRUE set statusPTR to error message: END_STP = 0b10100000 (160_dec A0_hex)
*/
void checkEndstop()
{
    if(getEndstopGPIO() == TRUE)
    {  
        char str[30];
        sprintf(str, "\r\n\n\n ENDSTOP AKTIVERET \r\n\n\n");
        debugOut_PutString(str);
        i2cPtr_[4] = 0b10100000;
        endstopStatusPtr_ = 0;
        lukSystem();
    }
}

CY_ISR(loopIsr)
{
    if(ready == TRUE) 
    {
        lukSystem();
    }
    ready = TRUE;
}

void error(char* str)
{
    debugOut_PutString(str);    
    while(TRUE);
}

/* [] END OF FILE */
