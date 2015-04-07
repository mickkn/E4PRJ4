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

#include <device.h>
#include <stdio.h>
#include <fixedMath.h>

/* Macro definitions */
#define DEBUG 1

//sample rate and sample period
#define FS 100
#define DT (1 << 2^16)/FS //dt defined as a 16.16 fixed point number

/* The scale factor of the ITG3200 gyroscope is 14.375 Lsb per  *
 * deg/s, converted to 16.16 fixed point. (2^16/14.375)         */
#define GYRO_SCALE_FACTOR 4559
/* The accelerometer scale factor of the ADXL345 in +- 4g range *
 * is 128Lsb per g, converted to 16.16 fixed point. (2^16/2^7)  */
#define ACC_SCALE_FACTOR 512

// 180 and 360 in 16.16 fixed point
#define DEG_180 (180 << 16)
#define DEG_360 (360 << 16)

#define GYRO_WEIGHT 62259 //0.95 * 2^16
#define ACC_WEIGHT 0x100 - GYRO_WEIGHT // (1 - gyro_weight) * 2^16

//I2C defines
#define GYRO_ADDRESS 0x68 //7 bit right justified
#define ACC_ADDRESS 0x53 //7 bit right justified

#define ACC_INIT_LEN 5
#define GYRO_INIT_LEN 4

#define ACC_Y_OFFSET 0
#define ACC_Z_OFFSET 0

#define GYRO_FIRST_DATA 0x1D //this is X_H which will be followed by X_L
#define ACC_FIRST_DATA 0x34 //first in seq. Y_L, Y_H, Z_L, Z_H

/* Global constants */
const uint8_t accInitArray[ACC_INIT_LEN][2] = {
    {0x1F, ACC_Y_OFFSET}, // calibration of y axis
    {0x20, ACC_Z_OFFSET}, // calibration of z axis
    {0x31, 0x01},         // set to +-4g range
    {0x2D, 0x12},         // activate meassurements
    {0x2D, 0x08},         // activate meassurements
};

const uint8_t gyroInitArray[GYRO_INIT_LEN][2] = {
    {0x15, 0x09},         /* set the sample rate to 100Hz (1kHz/9+1) */
    {0x16, 0x1B},         /* set full range mode and 42Hz cutoff for *
                           * internal filter                         */
    {0x17, 0x01},         /* configure device to send data rdy int   */
    {0x3E, 0x19}          /* put y and z gyro in standby and select  *
                           * x gyro for clock                        */       
};

/* Global variables */
volatile uint8 dataReady = 0;
volatile fix16_t accData[2] = {0, 0}, gyroData = 0;
fix16_t estAng = 0;

/* Function prototypes */
void setupI2CDevice(uint8_t addr, const uint8_t initArray[][2] , uint8_t arrayLen);    
uint8_t readI2CReg(uint8_t addr, uint8_t reg);
void writeI2CReg(uint8_t addr, uint8_t reg, uint8_t val);
CY_ISR_PROTO(gyroDataReadyInterrupt);


/* Function implementations */
int main()
{
    /* Start the Components */
    UART_Start();
    I2C_Start();
   
    
    /* Setup the accelerometer and gyro */
    setupI2CDevice(GYRO_ADDRESS, gyroInitArray, GYRO_INIT_LEN);
    setupI2CDevice(ACC_ADDRESS, accInitArray, ACC_INIT_LEN);
    PWM_1_Start();
    
    /* Enable global interrupts */
    GYRO_DR_INT_StartEx(&gyroDataReadyInterrupt);
    CyGlobalIntEnable;
    
    /*print opening msg*/
     UART_UartPutString("Hello\r\n");
//    char str[10];
//    int i;
//    int j;
//    for(j = 0; j < 10; j++)
//    {
//        for(i = 0; i <= 0x3E; i++)
//        {
//            sprintf(str, "* %d-%d *", i, readI2CReg(ACC_ADDRESS, i));
//            UART_UartPutString(str);
//        }
//        UART_UartPutString("\r\n*************\r\n");
//        
//    }
    UART_UartPutString("World!\r\n");
   
    /*Data processing loop*/
    while(1){
      
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
    I2C_I2CMasterSendStart(addr, 0);
    I2C_I2CMasterWriteByte(reg);
    I2C_I2CMasterSendRestart(addr, 1);
    uint8_t result = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    I2C_I2CMasterSendStop();
    return result;
}

void writeI2CReg(uint8_t addr, uint8_t reg, uint8_t val){
    I2C_I2CMasterSendStart(addr, 0);
    I2C_I2CMasterWriteByte(reg);
    I2C_I2CMasterWriteByte(val);
    I2C_I2CMasterSendStop();
}

CY_ISR(gyroDataReadyInterrupt)
{
    //read raw data from gyro
    int16_t rawGyroX = readI2CReg(GYRO_ADDRESS, GYRO_FIRST_DATA+1) + ((int16_t) readI2CReg(GYRO_ADDRESS, GYRO_FIRST_DATA) << 8);
    
    // gyro data is scaled to 16.16 fixed point by using the GYRO_SCALE_FACTOR.
    gyroData = rawGyroX * GYRO_SCALE_FACTOR;
    
    //read the raw data from the accellerometer
    int16 rawAccY = readI2CReg(ACC_ADDRESS, ACC_FIRST_DATA) + ((int16_t) readI2CReg(ACC_ADDRESS, ACC_FIRST_DATA + 1)<<8);
    int16 rawAccZ = readI2CReg(ACC_ADDRESS, ACC_FIRST_DATA+2) + ((int16_t) readI2CReg(ACC_ADDRESS, ACC_FIRST_DATA + 3)<<8);
    
    // acc data is scaled to 16.16 fixed point by using the ACC_SCALE_FACTOR.                                                    */
    accData[0] = ((fix16_t) rawAccY) * ACC_SCALE_FACTOR; 
    accData[1] = ((fix16_t) rawAccZ) * ACC_SCALE_FACTOR;       
    
    // Integrate gyro data over last sample period, and check for angle wraparound                                      */
    estAng += fix16mul(gyroData, DT);
    if(estAng < -DEG_180) estAng += DEG_360; 
    if(estAng > DEG_180) estAng -= DEG_360; 
        
    /* Correct angle estimate using accelerometer data if it is estimated valid. *
     * The acc input can be used if the accelleration vector has a length close  *
     * to 1g (no force other than gravity), which is estimated by the sum of the *
     * components for computational efficiency.                                  */
    fix16_t forceMagEst = fix16abs(accData[0]) + fix16abs(accData[1]);
    // Use if forcemag is between 0.5*(2^16) and 2*(2^16)
    if(1<<15 < forceMagEst && forceMagEst < 1<<17) 
    {
        //take part of gyro estimate and add complementary part of acc estimate
        estAng = fix16mul(GYRO_WEIGHT, estAng) 
                 + fix16mul(ACC_WEIGHT, fix16rad2deg(fix16atan2(accData[0], accData[1])));
    }    
        
        
    //print result
    CyPins_SetPin(Pin_1_0);
    char result[15];
    sprintf(result, "%d, ", (int) estAng);
    UART_UartPutString(result);
    CyPins_ClearPin(Pin_1_0);
}
                
/* [] END OF FILE */
