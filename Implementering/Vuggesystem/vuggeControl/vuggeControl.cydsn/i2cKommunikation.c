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
// FILENAME : i2cKommunikation.c
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : h file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of i2cKommunikation.c
// 0.2	30-04-2015 - Jeppe - EZI2C implemented
// 0.3	09-04-2015 - Jeppe - I2C tested
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - SensorFortolker needs finished implementation
// 0.3 - Non known issuses
//========================================================================
// includes
#include "i2cKommunikation.h"

// Function declarations

    

/* Function Name: initI2C
   Summary:
    Sets up the I2C bus, and enables it.
*/
void initI2C(void)
{
    I2CBuf[I2C_ID_REG] = 0xFB; // ID
    I2CBuf[I2C_ONOFF_REG] = 0xF0; // ON_OFF
    I2CBuf[I2C_FREK_REG] = 0x00; // Frekvens
    I2CBuf[I2C_VINK_REG] = 0x00; // Vinkeludsving
    I2CBuf[I2C_STAT_REG] = 0x00; // Status
   
    I2CVuggesystem_EzI2CSetAddress1(I2C_DEV_ADDR);
    I2CVuggesystem_EzI2CSetBuffer1(I2C_BUF_SIZE,4,&I2CBuf[0]);
    I2CVuggesystem_Start();
    
}

/* Function Name: sendConKom
   Summary:
    Returns pointer to I2C transmite buffer
*/
uint8* sendConKom()
{
    return I2CBuf;
}


/* [] END OF FILE */
