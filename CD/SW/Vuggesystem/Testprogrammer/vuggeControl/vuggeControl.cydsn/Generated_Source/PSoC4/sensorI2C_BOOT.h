/*******************************************************************************
* File Name: sensorI2C_BOOT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the bootloader
*  communication interface of SCB component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_sensorI2C_H)
#define CY_SCB_BOOT_sensorI2C_H

#include "sensorI2C_PVT.h"

#if (sensorI2C_SCB_MODE_I2C_INC)
    #include "sensorI2C_I2C.h"
#endif /* (sensorI2C_SCB_MODE_I2C_INC) */

#if (sensorI2C_SCB_MODE_EZI2C_INC)
    #include "sensorI2C_EZI2C.h"
#endif /* (sensorI2C_SCB_MODE_EZI2C_INC) */

#if (sensorI2C_SCB_MODE_SPI_INC || sensorI2C_SCB_MODE_UART_INC)
    #include "sensorI2C_SPI_UART.h"
#endif /* (sensorI2C_SCB_MODE_SPI_INC || sensorI2C_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define sensorI2C_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_sensorI2C) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (sensorI2C_SCB_MODE_I2C_INC)

    #define sensorI2C_I2C_BTLDR_COMM_ENABLED     (sensorI2C_BTLDR_COMM_ENABLED && \
                                                            (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             sensorI2C_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void sensorI2C_I2CCyBtldrCommStart(void);
    void sensorI2C_I2CCyBtldrCommStop (void);
    void sensorI2C_I2CCyBtldrCommReset(void);
    cystatus sensorI2C_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus sensorI2C_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define sensorI2C_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define sensorI2C_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define sensorI2C_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define sensorI2C_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_I2C_BTLDR_COMM_ENABLED) */

#endif /* (sensorI2C_SCB_MODE_I2C_INC) */


#if (sensorI2C_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define sensorI2C_EZI2C_BTLDR_COMM_ENABLED   (sensorI2C_BTLDR_COMM_ENABLED && \
                                                         sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void sensorI2C_EzI2CCyBtldrCommStart(void);
    void sensorI2C_EzI2CCyBtldrCommStop (void);
    void sensorI2C_EzI2CCyBtldrCommReset(void);
    cystatus sensorI2C_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus sensorI2C_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (sensorI2C_SCB_MODE_EZI2C_INC) */

#if (sensorI2C_SCB_MODE_SPI_INC || sensorI2C_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define sensorI2C_SPI_BTLDR_COMM_ENABLED     (sensorI2C_BTLDR_COMM_ENABLED && \
                                                        sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)

    #define sensorI2C_UART_BTLDR_COMM_ENABLED    (sensorI2C_BTLDR_COMM_ENABLED && \
                                                        sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void sensorI2C_SpiCyBtldrCommStart(void);
    void sensorI2C_SpiCyBtldrCommStop (void);
    void sensorI2C_SpiCyBtldrCommReset(void);
    cystatus sensorI2C_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus sensorI2C_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void sensorI2C_UartCyBtldrCommStart(void);
    void sensorI2C_UartCyBtldrCommStop (void);
    void sensorI2C_UartCyBtldrCommReset(void);
    cystatus sensorI2C_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus sensorI2C_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_UART_BTLDR_COMM_ENABLED) */

#endif /* (sensorI2C_SCB_MODE_SPI_INC || sensorI2C_SCB_MODE_UART_INC) */

#if !defined (sensorI2C_I2C_BTLDR_COMM_ENABLED)
    #define sensorI2C_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (sensorI2C_I2C_BTLDR_COMM_ENABLED) */

#if !defined (sensorI2C_EZI2C_BTLDR_COMM_ENABLED)
    #define sensorI2C_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (sensorI2C_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (sensorI2C_SPI_BTLDR_COMM_ENABLED)
    #define sensorI2C_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (sensorI2C_SPI_BTLDR_COMM_ENABLED) */

#if !defined (sensorI2C_UART_BTLDR_COMM_ENABLED)
    #define sensorI2C_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (sensorI2C_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define sensorI2C_BTLDR_COMM_MODE_ENABLED    (sensorI2C_I2C_BTLDR_COMM_ENABLED   || \
                                                     sensorI2C_EZI2C_BTLDR_COMM_ENABLED || \
                                                     sensorI2C_SPI_BTLDR_COMM_ENABLED   || \
                                                     sensorI2C_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_BTLDR_COMM_ENABLED)
    #if (sensorI2C_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void sensorI2C_CyBtldrCommStart(void);
        void sensorI2C_CyBtldrCommStop (void);
        void sensorI2C_CyBtldrCommReset(void);
        cystatus sensorI2C_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus sensorI2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (sensorI2C_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_sensorI2C)
        #define CyBtldrCommStart    sensorI2C_CyBtldrCommStart
        #define CyBtldrCommStop     sensorI2C_CyBtldrCommStop
        #define CyBtldrCommReset    sensorI2C_CyBtldrCommReset
        #define CyBtldrCommWrite    sensorI2C_CyBtldrCommWrite
        #define CyBtldrCommRead     sensorI2C_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_sensorI2C) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_sensorI2C_H) */

/* [] END OF FILE */
