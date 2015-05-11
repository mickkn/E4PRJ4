/*******************************************************************************
* File Name: I2CVuggesystem_BOOT.h
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

#if !defined(CY_SCB_BOOT_I2CVuggesystem_H)
#define CY_SCB_BOOT_I2CVuggesystem_H

#include "I2CVuggesystem_PVT.h"

#if (I2CVuggesystem_SCB_MODE_I2C_INC)
    #include "I2CVuggesystem_I2C.h"
#endif /* (I2CVuggesystem_SCB_MODE_I2C_INC) */

#if (I2CVuggesystem_SCB_MODE_EZI2C_INC)
    #include "I2CVuggesystem_EZI2C.h"
#endif /* (I2CVuggesystem_SCB_MODE_EZI2C_INC) */

#if (I2CVuggesystem_SCB_MODE_SPI_INC || I2CVuggesystem_SCB_MODE_UART_INC)
    #include "I2CVuggesystem_SPI_UART.h"
#endif /* (I2CVuggesystem_SCB_MODE_SPI_INC || I2CVuggesystem_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define I2CVuggesystem_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2CVuggesystem) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (I2CVuggesystem_SCB_MODE_I2C_INC)

    #define I2CVuggesystem_I2C_BTLDR_COMM_ENABLED     (I2CVuggesystem_BTLDR_COMM_ENABLED && \
                                                            (I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             I2CVuggesystem_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void I2CVuggesystem_I2CCyBtldrCommStart(void);
    void I2CVuggesystem_I2CCyBtldrCommStop (void);
    void I2CVuggesystem_I2CCyBtldrCommReset(void);
    cystatus I2CVuggesystem_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CVuggesystem_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define I2CVuggesystem_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define I2CVuggesystem_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define I2CVuggesystem_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define I2CVuggesystem_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED) */

#endif /* (I2CVuggesystem_SCB_MODE_I2C_INC) */


#if (I2CVuggesystem_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED   (I2CVuggesystem_BTLDR_COMM_ENABLED && \
                                                         I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void I2CVuggesystem_EzI2CCyBtldrCommStart(void);
    void I2CVuggesystem_EzI2CCyBtldrCommStop (void);
    void I2CVuggesystem_EzI2CCyBtldrCommReset(void);
    cystatus I2CVuggesystem_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CVuggesystem_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (I2CVuggesystem_SCB_MODE_EZI2C_INC) */

#if (I2CVuggesystem_SCB_MODE_SPI_INC || I2CVuggesystem_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define I2CVuggesystem_SPI_BTLDR_COMM_ENABLED     (I2CVuggesystem_BTLDR_COMM_ENABLED && \
                                                        I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG)

    #define I2CVuggesystem_UART_BTLDR_COMM_ENABLED    (I2CVuggesystem_BTLDR_COMM_ENABLED && \
                                                        I2CVuggesystem_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void I2CVuggesystem_SpiCyBtldrCommStart(void);
    void I2CVuggesystem_SpiCyBtldrCommStop (void);
    void I2CVuggesystem_SpiCyBtldrCommReset(void);
    cystatus I2CVuggesystem_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CVuggesystem_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void I2CVuggesystem_UartCyBtldrCommStart(void);
    void I2CVuggesystem_UartCyBtldrCommStop (void);
    void I2CVuggesystem_UartCyBtldrCommReset(void);
    cystatus I2CVuggesystem_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CVuggesystem_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_UART_BTLDR_COMM_ENABLED) */

#endif /* (I2CVuggesystem_SCB_MODE_SPI_INC || I2CVuggesystem_SCB_MODE_UART_INC) */

#if !defined (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED)
    #define I2CVuggesystem_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED) */

#if !defined (I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED)
    #define I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (I2CVuggesystem_SPI_BTLDR_COMM_ENABLED)
    #define I2CVuggesystem_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (I2CVuggesystem_SPI_BTLDR_COMM_ENABLED) */

#if !defined (I2CVuggesystem_UART_BTLDR_COMM_ENABLED)
    #define I2CVuggesystem_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (I2CVuggesystem_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define I2CVuggesystem_BTLDR_COMM_MODE_ENABLED    (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED   || \
                                                     I2CVuggesystem_EZI2C_BTLDR_COMM_ENABLED || \
                                                     I2CVuggesystem_SPI_BTLDR_COMM_ENABLED   || \
                                                     I2CVuggesystem_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_BTLDR_COMM_ENABLED)
    #if (I2CVuggesystem_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void I2CVuggesystem_CyBtldrCommStart(void);
        void I2CVuggesystem_CyBtldrCommStop (void);
        void I2CVuggesystem_CyBtldrCommReset(void);
        cystatus I2CVuggesystem_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus I2CVuggesystem_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (I2CVuggesystem_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2CVuggesystem)
        #define CyBtldrCommStart    I2CVuggesystem_CyBtldrCommStart
        #define CyBtldrCommStop     I2CVuggesystem_CyBtldrCommStop
        #define CyBtldrCommReset    I2CVuggesystem_CyBtldrCommReset
        #define CyBtldrCommWrite    I2CVuggesystem_CyBtldrCommWrite
        #define CyBtldrCommRead     I2CVuggesystem_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2CVuggesystem) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_I2CVuggesystem_H) */

/* [] END OF FILE */
