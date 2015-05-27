/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_I2Csensors_H)
#define CY_SCB_PVT_I2Csensors_H

#include "I2Csensors.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define I2Csensors_SetI2CExtClkInterruptMode(interruptMask) I2Csensors_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define I2Csensors_ClearI2CExtClkInterruptSource(interruptMask) I2Csensors_CLEAR_INTR_I2C_EC(interruptMask)
#define I2Csensors_GetI2CExtClkInterruptSource()                (I2Csensors_INTR_I2C_EC_REG)
#define I2Csensors_GetI2CExtClkInterruptMode()                  (I2Csensors_INTR_I2C_EC_MASK_REG)
#define I2Csensors_GetI2CExtClkInterruptSourceMasked()          (I2Csensors_INTR_I2C_EC_MASKED_REG)

#if (!I2Csensors_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define I2Csensors_SetSpiExtClkInterruptMode(interruptMask) \
                                                                I2Csensors_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define I2Csensors_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                I2Csensors_CLEAR_INTR_SPI_EC(interruptMask)
    #define I2Csensors_GetExtSpiClkInterruptSource()                 (I2Csensors_INTR_SPI_EC_REG)
    #define I2Csensors_GetExtSpiClkInterruptMode()                   (I2Csensors_INTR_SPI_EC_MASK_REG)
    #define I2Csensors_GetExtSpiClkInterruptSourceMasked()           (I2Csensors_INTR_SPI_EC_MASKED_REG)
#endif /* (!I2Csensors_CY_SCBIP_V1) */

#if(I2Csensors_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void I2Csensors_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (I2Csensors_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_I2Csensors_CUSTOM_INTR_HANDLER)
    extern cyisraddress I2Csensors_customIntrHandler;
#endif /* !defined (CY_REMOVE_I2Csensors_CUSTOM_INTR_HANDLER) */

extern I2Csensors_BACKUP_STRUCT I2Csensors_backup;

#if(I2Csensors_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 I2Csensors_scbMode;
    extern uint8 I2Csensors_scbEnableWake;
    extern uint8 I2Csensors_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 I2Csensors_mode;
    extern uint8 I2Csensors_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * I2Csensors_rxBuffer;
    extern uint8   I2Csensors_rxDataBits;
    extern uint32  I2Csensors_rxBufferSize;

    extern volatile uint8 * I2Csensors_txBuffer;
    extern uint8   I2Csensors_txDataBits;
    extern uint32  I2Csensors_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 I2Csensors_numberOfAddr;
    extern uint8 I2Csensors_subAddrSize;
#endif /* (I2Csensors_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(I2Csensors_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define I2Csensors_SCB_MODE_I2C_RUNTM_CFG     (I2Csensors_SCB_MODE_I2C      == I2Csensors_scbMode)
    #define I2Csensors_SCB_MODE_SPI_RUNTM_CFG     (I2Csensors_SCB_MODE_SPI      == I2Csensors_scbMode)
    #define I2Csensors_SCB_MODE_UART_RUNTM_CFG    (I2Csensors_SCB_MODE_UART     == I2Csensors_scbMode)
    #define I2Csensors_SCB_MODE_EZI2C_RUNTM_CFG   (I2Csensors_SCB_MODE_EZI2C    == I2Csensors_scbMode)
    #define I2Csensors_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (I2Csensors_SCB_MODE_UNCONFIG == I2Csensors_scbMode)

    /* Defines wakeup enable */
    #define I2Csensors_SCB_WAKE_ENABLE_CHECK       (0u != I2Csensors_scbEnableWake)
#endif /* (I2Csensors_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!I2Csensors_CY_SCBIP_V1)
    #define I2Csensors_SCB_PINS_NUMBER    (7u)
#else
    #define I2Csensors_SCB_PINS_NUMBER    (2u)
#endif /* (!I2Csensors_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_I2Csensors_H) */


/* [] END OF FILE */
