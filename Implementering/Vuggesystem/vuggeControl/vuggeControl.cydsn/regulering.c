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
// FILENAME : regulering.c
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : h file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of regulering.c
// 0.2	30-04-2015 - Jeppe - First writeup of MotorPWM module
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - Regulering needs finished implementation
//========================================================================
#include "regulering.h"
#include <fixedMath.h>
#include <stdio.h>

/*        --------------        FUNCTION DEFINITIONS       ---------------          */ 

/* Function Name: initRegulering
   Summary:
    Initiates regulering
*/
void initRegulering()
{
    prevFrek = 0;
    prevUdsving = 0;
    angleInc = 0; // the sine angle increment for each loop iteration with the current frequncy
    sineA = 0;
    reguleringsStatus_ = 0;
    going_up_ = TRUE;
    pwmSineAngle_ = 0;
    PWM_Start();
}

/* Function regParameter
   Summary:
    Receives the rocking parametres for the i2C reg and validates them
*/
void updateRegParameter(uint8 vuggefrekvens, uint8 vuggeudsving)
{
    if((vuggefrekvens == prevFrek) && (vuggeudsving == prevUdsving)) return;
    
    BOOL valid = FALSE;
    if((vuggefrekvens == 0) && (vuggeudsving == 0))// Vugge-niveau 0: 0 Hz (0) 0 grader (0)
    {
        valid = TRUE;
    }
    else if((vuggefrekvens == A_FREQ) && (vuggeudsving == A_ANGLE))// Vugge-niveau 1: 0,5 Hz (50) 10 grader (200)
    {
        valid = TRUE;
    }
    else if((vuggefrekvens == B_FREQ) && (vuggeudsving == B_ANGLE))// Vugge-niveau 2: 1 Hz (100) 6 grader (120)
    {
        valid = TRUE;
    }
    else if((vuggefrekvens) == C_FREQ && (vuggeudsving == C_ANGLE))// Vugge-niveau 3: 2 Hz (200) 4 grader (80)
    {
        valid = TRUE;
    }
    else if((vuggefrekvens == M_FREQ) && (vuggeudsving == M_ANGLE))// Manuel vugge-niveau : 0,75 Hz (75) 8 grader (160)
    {
        valid = TRUE;
    }
    
    if(valid)
    {
        /* peak peak value of desired sine in 16.16 fp is calculated as:                    *
         * vuggeUdsving * 20 * 2^16                                                         *
         * to account for i2c scale, and 16.16 scale respectively                           */
        sineA = vuggeudsving * 1310720;
        
        /* The incement of the angle per loop iteration is given by following formula:  *
         * angleInc = ((f_i2c*100)/loop_freq)*2^16 which becomes 2^15 * f_i2c           *
         * when loop freq = 200. f_i2c is the frequency read from the i2c reg not the   *
         * i2c frequency itself.                                                        */
        angleInc = vuggefrekvens << 15;
    }

}

/* Function Name: beregnRegulering
   Summary:
    Calculates a proportional regulator
*/
fix16_t beregnRegulering(fix16_t currentAngle)
{
    //update sine time
    if(pwmSineAngle_ >= FIXED_HALF_PI)
    {
        going_up_ = FALSE;
    } 
    else if (pwmSineAngle_ <= -FIXED_HALF_PI)
    {
        going_up_ = TRUE;
    }
    if(going_up_)  pwmSineAngle_ += angleInc;
    else          pwmSineAngle_ -= angleInc;
    
    //calculate desired angle:
    fix16_t R = fix16mul(sineA, fix16sin(pwmSineAngle_));
    fix16_t e = R - currentAngle;
    fix16_t C = K_P * e;
    return C;
    // Sæt evt regulerings status her - ERR = 0b10000000(128_dec 80_hex) , STALL 0b11000000(192_dec C0_hex)
}

/* Function Name: PWMStyring
   Summary:
     ??
*/
void PWMStyring(fix16_t intensity)
{
    uint8_t comp = (fix16mul(intensity, 52429)+6553600)>>16;
    PWM_WriteCompare(comp);
}


/* Function Name: getReguleringsStatus
   Summary:
    Returns pointer to reguleringsStatus_
*/
int* getReguleringsStatus()
{
    int* reguleringStatPtr = &reguleringsStatus_;
    return reguleringStatPtr;
}

/*        --------------        END FUNCTION DEFINITIONS       ---------------          */ 

/* [] END OF FILE */
