#ifndef SENSORFORTOLKER_H
#define SENSORFORTOLKER_H
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
// FILENAME : sensorFortolker.h
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : h file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of vuggeControl.c
// 0.2	30-04-2015 - Jeppe - EndstopGPIO implemented
// 0.3	23-05-2015 - Felix Blix - Proper implemented
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - SensorFortolker needs finished implementation
// 0.3 - Motor positionssensor not implemented
//========================================================================
   
/*      Public function prototypes       */
    
//initialize sensors
void initSensors(void);

//returns the motor position - not impl.
//fix16_t getMotorPosSens(void);

//returns the angle of the baby carriage
fix16_t getVuggeUdsvingSens(void);

//return the status of the endstop
BOOL getEndstopGPIO();

/*     private function prototypes       */
void setupI2CDevice(uint8_t addr, const uint8_t initArray[][2] , uint8_t arrayLen);    
uint8_t readI2CReg(uint8_t addr, uint8_t reg);
void writeI2CReg(uint8_t addr, uint8_t reg, uint8_t val);
void readGyroData(fix16_t* gyroData);
void readAccData(fix16_t* accData);
CY_ISR_PROTO(gyroDataReadyInterrupt);
CY_ISR_PROTO(EndstopGPIO);

#endif
/* [] END OF FILE */
