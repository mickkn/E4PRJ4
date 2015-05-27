#ifndef REGULERING_H
#define REGULERING_H
#include "globals.h"
#include "fixedMath.h"
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
// FILENAME : regulering.h
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : h file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of regulering.h
// 0.2	30-04-2015 - Jeppe - First writeup of MotorPWM module
// 0.3	23-05-2015 - Jeppe and Felix Blix - First write up of control implemented
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - Regulering needs finished implementation
// 0.3 - Needs proper control
//========================================================================

// Definitons
#define K_P 491520 //a factor of 20 gives a maximum correction at a 5 degree error.
#define K_D 6144 // Derivative factor K_P/8
#define K_I 65536
#define hysterese 10
    
#define A_FREQ 0x08 	// 0.08 Hz (50) 
#define A_ANGLE 0xC8	// 10 grader (200)

#define B_FREQ 0x10     // 0.16 Hz (100)
#define B_ANGLE 0x78	// 6 grader (120)

#define C_FREQ 0x20	    // 0.32 Hz (200)
#define C_ANGLE 0x50	// 4 grader (80) 

#define M_FREQ 0x0C	    // 0.12 Hz (75)
#define M_ANGLE 0xA0	// 8 grader (160)
    
// Attributes
int* sensorDataPtr_;
int fixedPointReg_;
int reguleringsStatus_;
BOOL going_up_;
fix16_t pwmSineAngle_;
    
/* ****Debug**** */
fix16_t print1;
fix16_t print2;

uint8_t prevFrek;
uint8_t prevUdsving;
fix16_t angleInc; // the sine angle increment for each loop iteration with the current frequncy
fix16_t sineA; // the peak to peak value of desired rocking angle 16.16 fp degrees.
fix16_t prev_e;
fix16_t i_e;

    
// Function prototypes
void initRegulering();
void updateRegParameter(uint8, uint8);
void PWMStyring(fix16_t intensity);
fix16_t beregnRegulering(fix16_t currentAngle);
int* getReguleringsStatus();

#endif
/* [] END OF FILE */
