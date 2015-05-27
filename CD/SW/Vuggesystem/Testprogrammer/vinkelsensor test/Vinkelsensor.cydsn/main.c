/*******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:
*  
*
********************************************************************************
* 
*******************************************************************************/

#include <project.h>
#include <stdio.h>
#include <fixedMath.h>

/* Macro definitions */
#define DEBUG 1

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

// 180 and 360 in 16.16 fixed point
#define DEG_180 11796480 //(180 << 16)
#define DEG_360 23592960 //(360 << 16)

#define GYRO_WEIGHT 58982 //0.90 * 2^16
#define ACC_WEIGHT 6554 // (1 - gyro_weight) * 2^16

//I2C defines
#define IMU_ADDRESS 0b1101000 //+1 for alt
//#define GYRO_ADDRESS 0x68 //7 bit right justified
//#define ACC_ADDRESS 0x53 //7 bit right justified

#define IMU_INIT_LEN 5
//#define ACC_INIT_LEN 5
//#define GYRO_INIT_LEN 4
//#define ACC_Y_OFFSET 0
//#define ACC_Z_OFFSET 0

#define GYRO_FIRST_DATA 0x43 //this is X_H which will be followed by X_L
#define ACC_FIRST_DATA 0x3D //first in seq. Y_H, Y_L, Z_H, Z_L

#define SAMPLE_SIZE 190

/* Global constants */

const uint8_t imuInitArray[IMU_INIT_LEN][2] = {
    {0x19, 4},              //set the datarate to 200Hz (1kHz/1+4)
    {0x1A, 5},              //set dlpf freq to 10 Hz
    {0x1B, 24},             //gyro range = +/-2000 deg/s
    {0x1C, 8},              //acc range = +/-4g
    {0x6B, 1}               //set clk source to x gyro
};


//const uint8_t accInitArray[ACC_INIT_LEN][2] = {
//    {0x1F, ACC_Y_OFFSET}, // calibration of y axis
//    {0x20, ACC_Z_OFFSET}, // calibration of z axis
//    {0x31, 0x01},         // set to +-4g range
//    {0x2D, 0x12},         // activate meassurements
//    {0x2D, 0x08},         // activate meassurements
//};
//
//const uint8_t gyroInitArray[GYRO_INIT_LEN][2] = {
//    {0x15, 0x03},         /* set the sample rate to 250Hz (1kHz/3+1) */
//    {0x16, 0x1B},         /* set full range mode and 42Hz cutoff for *
//                           * internal filter                         */
//    {0x17, 0x01},         /* configure device to send data rdy int   */
//    {0x3E, 0x03}           //00 for debug normal 0x19 /* put y and z gyro in standby and select  *
//                           /* x gyro for clock                        */       
//};

/* Global variables */
volatile uint8 dataReady = 0;
fix16_t accData[2] = {0, 0}, gyroData = 0;
fix16_t gyroAng = 0, accAng = 0, estAng = 0;

/* Function prototypes */
void setupI2CDevice(uint8_t addr, const uint8_t initArray[][2] , uint8_t arrayLen);    
uint8_t readI2CReg(uint8_t addr, uint8_t reg);
void writeI2CReg(uint8_t addr, uint8_t reg, uint8_t val);
void readGyroData(fix16_t* gyroData);
void readAccData(fix16_t* accData);
CY_ISR_PROTO(gyroDataReadyInterrupt);


int main()
{
    /* Start the Components */
    UART_Start();
    I2C_Start();
    DATA_TIMER_Start();
    
    UART_UartPutString("\r\n\r\nHello ");
    
    /* Setup the accelerometer and gyro */
    //setupI2CDevice(GYRO_ADDRESS, gyroInitArray, GYRO_INIT_LEN);
    //setupI2CDevice(ACC_ADDRESS, accInitArray, ACC_INIT_LEN);
    setupI2CDevice(IMU_ADDRESS, imuInitArray, IMU_INIT_LEN);
      
    /*print opening msg*/
    UART_UartPutString(" World!\r\n\r\n");
    
    /* Enable global interrupts */
    GYRO_DR_INT_StartEx(&gyroDataReadyInterrupt);    
    
    fix16_t gyroAng = 0;
    CyGlobalIntEnable;
    while(1)
    {
        //wait for data
        CyPins_ClearPin(Pin_1_0);
        while(dataReady == 0);
        CyPins_SetPin(Pin_1_0);
        //read sensor data
        readGyroData(&gyroData);
        readAccData(accData);
        
        // Integrate gyro data over last sample period, and calculate new angle from gyro                                      */
        estAng += fix16mul(gyroData, DT);
        
        // wrap angle if outside +/- 180 area
        if(estAng < -DEG_180) estAng += DEG_360; 
        if(estAng > DEG_180) estAng -= DEG_360; 
        
        /* Correct angle estimate using accelerometer data if it is estimated valid. *
         * The acc input can be used if the accelleration vector has a length close  *
         * to 1g (no force other than gravity), which is estimated by the sum of the *
         * components for computational efficiency.                                  */
        fix16_t forceMagEst = fix16abs(accData[0]) + fix16abs(accData[1]);
        
        // Use if forcemag is between 0.9*(2^16) and 1.4*(2^16)
        fix16_t accAng = 0;
        if(58982 < forceMagEst && forceMagEst < 91750) 
        {
            accAng = fix16rad2deg(FIXED_HALF_PI + fix16atan2(accData[1], accData[0]));
            //take part of gyro estimate and add complementary part of acc estimate
            estAng = fix16mul(GYRO_WEIGHT, estAng) 
                     + fix16mul(ACC_WEIGHT, accAng);
        }    
            
        //scale compensation:
        fix16_t ang = fix16mul(estAng, 58982);
        //print result
        
        char result[15];
        sprintf(result, "%d, ", ang);
        UART_UartPutString(result);
        dataReady = 0;
    }
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
    
	if (I2C_I2CMasterSendStart(addr, 0) == I2C_I2C_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    { 
        if(I2C_I2CMasterWriteByte(reg) == I2C_I2C_MSTR_NO_ERROR)
		{
            if(I2C_I2CMasterSendRestart(addr, 1) == I2C_I2C_MSTR_NO_ERROR)
			{
                result = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
                I2C_I2CMasterSendStop();
				
			}
		}
	}
	return result;		
    
}

void writeI2CReg(uint8_t addr, uint8_t reg, uint8_t val){
    //I2C_I2CMasterSendStart(addr, 0);
    //I2C_I2CMasterWriteByte(reg);
    //I2C_I2CMasterWriteByte(val);
    //I2C_I2CMasterSendStop();
   
    
	if (I2C_I2CMasterSendStart(addr, 0) == I2C_I2C_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    { 
        if(I2C_I2CMasterWriteByte(reg) == I2C_I2C_MSTR_NO_ERROR)
		{
              if(I2C_I2CMasterWriteByte(val) == I2C_I2C_MSTR_NO_ERROR)   
                {      
                    I2C_I2CMasterSendStop();
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

void error(char* str)
{
    UART_UartPutString(str);
    while(1);
}

CY_ISR(gyroDataReadyInterrupt)
{
    //if dataReady flag has not been cleared, the system is lagging.
    if(dataReady == 1) error("\r\n\nLag Error!\r\n\n");
    //else set data ready flag
    dataReady = 1;
}
                
/* [] END OF FILE */
