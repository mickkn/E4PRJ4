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

#if !defined(CY_SCB_PVT_I2CVuggesystem_H)
#define CY_SCB_PVT_I2CVuggesystem_H

#include "I2CVuggesystem.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define I2CVuggesystem_SetI2CExtClkInterruptMode(interruptMask) I2CVuggesystem_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define I2CVuggesystem_ClearI2CExtClkInterruptSource(interruptMask) I2CVuggesystem_CLEAR_INTR_I2C_EC(interruptMask)
#define I2CVuggesystem_GetI2CExtClkInterruptSource()                (I2CVuggesystem_INTR_I2C_EC_REG)
#define I2CVuggesystem_GetI2CExtClkInterruptMode()                  (I2CVuggesystem_INTR_I2C_EC_MASK_REG)
#define I2CVuggesystem_GetI2CExtClkInterruptSourceMasked()          (I2CVuggesystem_INTR_I2C_EC_MASKED_REG)

#if (!I2CVuggesystem_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define I2CVuggesystem_SetSpiExtClkInterruptMode(interruptMask) \
                                                                I2CVuggesystem_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define I2CVuggesystem_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                I2CVuggesystem_CLEAR_INTR_SPI_EC(interruptMask)
    #define I2CVuggesystem_GetExtSpiClkInterruptSource()                 (I2CVuggesystem_INTR_SPI_EC_REG)
    #define I2CVuggesystem_GetExtSpiClkInterruptMode()                   (I2CVuggesystem_INTR_SPI_EC_MASK_REG)
    #define I2CVuggesystem_GetExtSpiClkInterruptSourceMasked()           (I2CVuggesystem_INTR_SPI_EC_MASKED_REG)
#endif /* (!I2CVuggesystem_CY_SCBIP_V1) */

#if(I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void I2CVuggesystem_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_I2CVuggesystem_CUSTOM_INTR_HANDLER)
    extern cyisraddress I2CVuggesystem_customIntrHandler;
#endif /* !defined (CY_REMOVE_I2CVuggesystem_CUSTOM_INTR_HANDLER) */

extern I2CVuggesystem_BACKUP_STRUCT I2CVuggesystem_backup;

#if(I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 I2CVuggesystem_scbMode;
    extern uint8 I2CVuggesystem_scbEnableWake;
    extern uint8 I2CVuggesystem_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 I2CVuggesystem_mode;
    extern uint8 I2CVuggesystem_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * I2CVuggesystem_rxBuffer;
    extern uint8   I2CVuggesystem_rxDataBits;
    extern uint32  I2CVuggesystem_rxBufferSize;

    extern volatile uint8 * I2CVuggesystem_txBuffer;
    extern uint8   I2CVuggesystem_txDataBits;
    extern uint32  I2CVuggesystem_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 I2CVuggesystem_numberOfAddr;
    extern uint8 I2CVuggesystem_subAddrSize;
#endif /* (I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define I2CVuggesystem_SCB_MODE_I2C_RUNTM_CFG     (I2CVuggesystem_SCB_MODE_I2C      == I2CVuggesystem_scbMode)
    #define I2CVuggesystem_SCB_MODE_SPI_RUNTM_CFG     (I2CVuggesystem_SCB_MODE_SPI      == I2CVuggesystem_scbMode)
    #define I2CVuggesystem_SCB_MODE_UART_RUNTM_CFG    (I2CVuggesystem_SCB_MODE_UART     == I2CVuggesystem_scbMode)
    #define I2CVuggesystem_SCB_MODE_EZI2C_RUNTM_CFG   (I2CVuggesystem_SCB_MODE_EZI2C    == I2CVuggesystem_scbMode)
    #define I2CVuggesystem_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (I2CVuggesystem_SCB_MODE_UNCONFIG == I2CVuggesystem_scbMode)

    /* Defines wakeup enable */
    #define I2CVuggesystem_SCB_WAKE_ENABLE_CHECK       (0u != I2CVuggesystem_scbEnableWake)
#endif /* (I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!I2CVuggesystem_CY_SCBIP_V1)
    #define I2CVuggesystem_SCB_PINS_NUMBER    (7u)
#else
    #define I2CVuggesystem_SCB_PINS_NUMBER    (2u)
#endif /* (!I2CVuggesystem_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_I2CVuggesystem_H) */


/* [] END OF FILE */
