/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_sensorI2C_H)
#define CY_SCB_I2C_PVT_sensorI2C_H

#include "sensorI2C_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 sensorI2C_state; /* Current state of I2C FSM */

#if(sensorI2C_I2C_SLAVE_CONST)
    extern volatile uint8 sensorI2C_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * sensorI2C_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  sensorI2C_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  sensorI2C_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * sensorI2C_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  sensorI2C_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  sensorI2C_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  sensorI2C_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   sensorI2C_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (sensorI2C_I2C_SLAVE_CONST) */

#if(sensorI2C_I2C_MASTER_CONST)
    extern volatile uint16 sensorI2C_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  sensorI2C_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * sensorI2C_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  sensorI2C_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  sensorI2C_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * sensorI2C_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  sensorI2C_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  sensorI2C_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  sensorI2C_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (sensorI2C_I2C_MASTER_CONST) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(sensorI2C_SCB_MODE_I2C_CONST_CFG)
    void sensorI2C_I2CInit(void);
#endif /* (sensorI2C_SCB_MODE_I2C_CONST_CFG) */

void sensorI2C_I2CStop(void);
void sensorI2C_I2CSaveConfig(void);
void sensorI2C_I2CRestoreConfig(void);

#if(sensorI2C_I2C_MASTER_CONST)
    void sensorI2C_I2CReStartGeneration(void);
#endif /* (sensorI2C_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_sensorI2C_H) */


/* [] END OF FILE */
