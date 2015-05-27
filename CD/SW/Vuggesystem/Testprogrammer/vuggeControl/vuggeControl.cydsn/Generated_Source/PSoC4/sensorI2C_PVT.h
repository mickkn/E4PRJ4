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

#if !defined(CY_SCB_PVT_sensorI2C_H)
#define CY_SCB_PVT_sensorI2C_H

#include "sensorI2C.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define sensorI2C_SetI2CExtClkInterruptMode(interruptMask) sensorI2C_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define sensorI2C_ClearI2CExtClkInterruptSource(interruptMask) sensorI2C_CLEAR_INTR_I2C_EC(interruptMask)
#define sensorI2C_GetI2CExtClkInterruptSource()                (sensorI2C_INTR_I2C_EC_REG)
#define sensorI2C_GetI2CExtClkInterruptMode()                  (sensorI2C_INTR_I2C_EC_MASK_REG)
#define sensorI2C_GetI2CExtClkInterruptSourceMasked()          (sensorI2C_INTR_I2C_EC_MASKED_REG)

#if (!sensorI2C_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define sensorI2C_SetSpiExtClkInterruptMode(interruptMask) \
                                                                sensorI2C_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define sensorI2C_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                sensorI2C_CLEAR_INTR_SPI_EC(interruptMask)
    #define sensorI2C_GetExtSpiClkInterruptSource()                 (sensorI2C_INTR_SPI_EC_REG)
    #define sensorI2C_GetExtSpiClkInterruptMode()                   (sensorI2C_INTR_SPI_EC_MASK_REG)
    #define sensorI2C_GetExtSpiClkInterruptSourceMasked()           (sensorI2C_INTR_SPI_EC_MASKED_REG)
#endif /* (!sensorI2C_CY_SCBIP_V1) */

#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void sensorI2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_sensorI2C_CUSTOM_INTR_HANDLER)
    extern cyisraddress sensorI2C_customIntrHandler;
#endif /* !defined (CY_REMOVE_sensorI2C_CUSTOM_INTR_HANDLER) */

extern sensorI2C_BACKUP_STRUCT sensorI2C_backup;

#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 sensorI2C_scbMode;
    extern uint8 sensorI2C_scbEnableWake;
    extern uint8 sensorI2C_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 sensorI2C_mode;
    extern uint8 sensorI2C_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * sensorI2C_rxBuffer;
    extern uint8   sensorI2C_rxDataBits;
    extern uint32  sensorI2C_rxBufferSize;

    extern volatile uint8 * sensorI2C_txBuffer;
    extern uint8   sensorI2C_txDataBits;
    extern uint32  sensorI2C_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 sensorI2C_numberOfAddr;
    extern uint8 sensorI2C_subAddrSize;
#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define sensorI2C_SCB_MODE_I2C_RUNTM_CFG     (sensorI2C_SCB_MODE_I2C      == sensorI2C_scbMode)
    #define sensorI2C_SCB_MODE_SPI_RUNTM_CFG     (sensorI2C_SCB_MODE_SPI      == sensorI2C_scbMode)
    #define sensorI2C_SCB_MODE_UART_RUNTM_CFG    (sensorI2C_SCB_MODE_UART     == sensorI2C_scbMode)
    #define sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG   (sensorI2C_SCB_MODE_EZI2C    == sensorI2C_scbMode)
    #define sensorI2C_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (sensorI2C_SCB_MODE_UNCONFIG == sensorI2C_scbMode)

    /* Defines wakeup enable */
    #define sensorI2C_SCB_WAKE_ENABLE_CHECK       (0u != sensorI2C_scbEnableWake)
#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!sensorI2C_CY_SCBIP_V1)
    #define sensorI2C_SCB_PINS_NUMBER    (7u)
#else
    #define sensorI2C_SCB_PINS_NUMBER    (2u)
#endif /* (!sensorI2C_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_sensorI2C_H) */


/* [] END OF FILE */
