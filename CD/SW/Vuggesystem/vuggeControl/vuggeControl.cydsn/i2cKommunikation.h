#ifndef I2CKOMMUNIKATION_H
#define I2CKOMMUNIKATION_H
#include <project.h>
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
// FILENAME : i2cKommunikation.h
// CREATED : 03-03-2015
// AUTHOR  : Jeppe Hofni
// DESCR.  : h file for PSoC4
//
//------------------------------------------------------------------------
//
// REV.  DATE/AUTHOR  CHANGE DESCRIPTION
// 0.1  03-03-2015 - Jeppe - First writeup of i2cKommunikation.h
// 0.2	30-04-2015 - Jeppe - EZI2C implemented
// 0.3	09-04-2015 - Jeppe - I2C tested
//------------------------------------------------------------------------
// KNOWN ISSUES:
// REV. - ISSUE(S)
// 0.1 - Needs to be sorted proper
// 0.2 - SensorFortolker needs finished implementation
// 0.3 - Non known issuses
//========================================================================

    
#define I2C_ID_REG 0x00
#define I2C_ONOFF_REG 0x01
#define I2C_FREK_REG 0x02
#define I2C_VINK_REG 0x03 
#define I2C_STAT_REG 0x04

#define I2C_BUF_SIZE (0x05u)

#define I2C_DEV_ADDR (0x08)

// Attributes
uint8 I2CBuf[I2C_BUF_SIZE]; //{ID, ON_OFF, Frekvens, Vinkeludsving, Status};


// Function prototypes
void initI2C(void);
uint8* sendConKom();


/* [] END OF FILE */
#endif