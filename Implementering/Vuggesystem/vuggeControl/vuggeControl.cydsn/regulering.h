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
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - Regulering needs finished implementation
//========================================================================

// Definitons
#define K_P 20 //a factor of 20 gives a maximum correction at a 5 degree error.
    
#define A_FREQ 0x32 	// 0,5 Hz (50) 
#define A_ANGLE 0xC8	// 10 grader (200)

#define B_FREQ 0x64     // 1 Hz (100)
#define B_ANGLE 0x78	// 6 grader (120)

#define C_FREQ 0xC8	    // 2 Hz (200)
#define C_ANGLE 0x50	// 4 grader (80) 

#define M_FREQ 0x4B	    // 0,75 Hz (75)
#define M_ANGLE 0xA0	// 8 grader (160)
    
// Attributes
int* sensorDataPtr_;
int fixedPointReg_;
int reguleringsStatus_;
BOOL going_up_;
fix16_t pwmSineAngle_;

uint8_t prevFrek;
uint8_t prevUdsving;
fix16_t angleInc; // the sine angle increment for each loop iteration with the current frequncy
fix16_t sineA; // the peak to peak value of desired rocking angle 16.16 fp degrees.

// Function prototypes
void initRegulering();
void updateRegParameter(uint8, uint8);
void PWMStyring(fix16_t intensity);
fix16_t beregnRegulering(fix16_t currentAngle);
int* getReguleringsStatus();

#endif
/* [] END OF FILE */
