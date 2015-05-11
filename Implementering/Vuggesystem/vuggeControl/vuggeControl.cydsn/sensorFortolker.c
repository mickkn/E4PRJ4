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
// FILENAME : sensorFortolker.c
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : c file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of vuggeControl.c
// 0.2	30-04-2015 - Jeppe - getEndstopGPIO implemented
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - SensorFortolker needs finished implementation
//========================================================================

//includes
#include "sensorFortolker.h"
#include <stdio.h>
#include <fixedMath.h>
#include "globals.h"

/*        -------------------        MACROS       --------------------          */
//sample rate and sample period
#define FS 200
#define DT 328 // 65536/FS //dt defined as a 16.16 fixed point number

/* The scale factor of the mpu6050 gyroscope is 16.4 Lsb per    *
 * deg/s, converted to 16.16 fixed point. (2^16/16.4  )         */
#define GYRO_SCALE_FACTOR 3996

/* The accelerometer scale factor of the mpu6050 accelerometer  *
 * in the +- 4g range is 8192 Lsb/g, converted to 16.16 fixed   *
 * point. (2^16/8192)                                           */
#define ACC_SCALE_FACTOR 8

#define GYRO_WEIGHT 58982 //0.90 * 2^16
#define ACC_WEIGHT 6554 // (1 - gyro_weight) * 2^16

//I2C defines
#define IMU_ADDRESS 0b1101000 //+1 for alt

#define GYRO_FIRST_DATA 0x43 //this is X_H which will be followed by X_L
#define ACC_FIRST_DATA 0x3D //first in seq. Y_H, Y_L, Z_H, Z_L

#define IMU_INIT_LEN 5
const uint8_t imuInitArray[IMU_INIT_LEN][2] = {
    {0x19, 4},              //set the datarate to 200Hz (1kHz/1+4)
    {0x1A, 3},              //set dlpf freq to 44 and 42 for acc and gyro respectively
    {0x1B, 24},             //gyro range = +/-2000 deg/s
    {0x1C, 8},              //acc range = +/-4g
    {0x6B, 1}               //set clk source to x gyro
};

/*        -------------------        END MACROS       --------------------          */

//flags
volatile BOOL dataReady = FALSE, endstop_ = FALSE;
//raw data
fix16_t accData[2] = {0, 0}, gyroData = 0;
//calculated angles
fix16_t gyroAng = 0, accAng = 0, estAng = 0;



/*        --------------        FUNCTION DEFINITIONS       ---------------          */ 

/* Function initSensor         *
 * Summary:                    *
 * Initialtes sensorFortolker  *
 * to operation status         */
void initSensors()
{
    /* Start the Components */
    sensorI2C_Start();
    //GYRO_DR_INT_StartEx(gyroDataReadyInterrupt);    
    Endstop_isr_StartEx(EndstopGPIO);
    
    /* Setup the accelerometer and gyro */
    setupI2CDevice(IMU_ADDRESS, imuInitArray, IMU_INIT_LEN);
}

///* Function getMotorPosSens
//   Summary:
//    ??
//*/
//fix16_t getMotorPosSens()
//{
//
//}

/* Function getVuggeUdsvingSens
   Summary:
    ??
*/
fix16_t getVuggeUdsvingSens()
{
     //read sensor data
    readGyroData(&gyroData);
    readAccData(accData);
    // Integrate gyro data over last sample period, and calculate new angle from gyro                                      */
    estAng += fix16mul(gyroData, DT);
    
    // wrap angle if outside +/- 180 area
    if(estAng < -FIXED_DEG_180) estAng += FIXED_DEG_360; 
    if(estAng > FIXED_DEG_180) estAng -= FIXED_DEG_360; 
    
    /* Correct angle estimate using accelerometer data if it is estimated valid. *
     * The acc input can be used if the accelleration vector has a length close  *
     * to 1g (no force other than gravity), which is estimated by the sum of the *
     * components for computational efficiency.                                  */
    fix16_t forceMagEst = fix16abs(accData[0]) + fix16abs(accData[1]);
    
    // Use if forcemag is between 0.95*(2^16) and 1.3*(2^16)
    fix16_t accAng = 0;
    if(62259 < forceMagEst && forceMagEst < 85197) 
    {
        accAng = fix16rad2deg(FIXED_HALF_PI + fix16atan2(accData[1], accData[0]));
        //take part of gyro estimate and add complementary part of acc estimate
        estAng = fix16mul(GYRO_WEIGHT, estAng) 
                 + fix16mul(ACC_WEIGHT, accAng);
    }    
    return estAng;
}

/* Function getEndstopGPIO
   Summary:
    Returns a ptr pointing at enstop_ adress
*/
BOOL getEndstopGPIO()
{
    return endstop_;
}

void setupI2CDevice(uint8_t addr, const uint8_t initArray[][2] , uint8_t arrayLen){
    int i;
    for(i = 0; i < arrayLen; i++){
        writeI2CReg(addr, initArray[i][0], initArray[i][1]);
    }
}
    
uint8_t readI2CReg(uint8_t addr, uint8_t reg)
{
    
    uint8_t result; 
    
	if (sensorI2C_I2CMasterSendStart(addr, 0) == sensorI2C_I2C_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    { 
        if(sensorI2C_I2CMasterWriteByte(reg) == sensorI2C_I2C_MSTR_NO_ERROR)
		{
            if(sensorI2C_I2CMasterSendRestart(addr, 1) == sensorI2C_I2C_MSTR_NO_ERROR)
			{
                result = sensorI2C_I2CMasterReadByte(sensorI2C_I2C_NAK_DATA);
                sensorI2C_I2CMasterSendStop();
				
			}
		}
	}
	return result;		
    
}

void writeI2CReg(uint8_t addr, uint8_t reg, uint8_t val){    
	if (sensorI2C_I2CMasterSendStart(addr, 0) == sensorI2C_I2C_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    { 
        if(sensorI2C_I2CMasterWriteByte(reg) == sensorI2C_I2C_MSTR_NO_ERROR)
		{
              if(sensorI2C_I2CMasterWriteByte(val) == sensorI2C_I2C_MSTR_NO_ERROR)   
                {      
                    sensorI2C_I2CMasterSendStop();
    		    }
		}
	}
	
    
    
}

void readGyroData(fix16_t* gyroData)
{
    //read the acc data from the accellerometer
    int16_t rawGyroX = readI2CReg(IMU_ADDRESS, GYRO_FIRST_DATA + 1) 
            + ((int16_t) readI2CReg(IMU_ADDRESS, GYRO_FIRST_DATA) << 8);
    //scale data and return it
    *gyroData = (fix16_t) rawGyroX * GYRO_SCALE_FACTOR;
}

void readAccData(fix16_t* accData)
{
    //read the raw data from the accellerometer
    int16 rawAccY = readI2CReg(IMU_ADDRESS, ACC_FIRST_DATA+1) 
            + ((int16_t) readI2CReg(IMU_ADDRESS, ACC_FIRST_DATA)<<8);
    int16 rawAccZ = readI2CReg(IMU_ADDRESS, ACC_FIRST_DATA+3) 
            + ((int16_t) readI2CReg(IMU_ADDRESS, ACC_FIRST_DATA + 2)<<8);
    //scale data and return it
    accData[0] = (fix16_t) rawAccY * ACC_SCALE_FACTOR; 
    accData[1] = (fix16_t) rawAccZ * ACC_SCALE_FACTOR;
}

/* interrupt definitions */

//Data ready interrupt from sensor
CY_ISR(gyroDataReadyInterrupt)
{
   //TODO: insert data interrupt code to improve data collection
}


/* ISR Function EndstopGPIO
   Summary:
    ISR triggers on Endstop activation and sets endstop_ flag high
*/
CY_ISR(EndstopGPIO)
{   
    endstop_ = 1;       
}

/*        --------------        END FUNCTION DEFINITIONS       ---------------          */ 

/* [] END OF FILE */
