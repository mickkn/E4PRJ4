/*******************************************************************************
* File Name: sensorI2C_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "sensorI2C_BOOT.h"


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_BTLDR_COMM_MODE_ENABLED)

/*******************************************************************************
* Function Name: sensorI2C_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_CyBtldrCommStart(void)
{
    #if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            sensorI2C_I2CCyBtldrCommStart();
        }
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            sensorI2C_SpiCyBtldrCommStart();
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            sensorI2C_UartCyBtldrCommStart();
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             sensorI2C_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
        sensorI2C_I2CCyBtldrCommStart();

    #elif(sensorI2C_SCB_MODE_SPI_CONST_CFG)
        sensorI2C_SpiCyBtldrCommStart();

    #elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
        sensorI2C_UartCyBtldrCommStart();

    #elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
        sensorI2C_EzI2CCyBtldrCommStart();

    #else
        /* Unknown mode */

    #endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: sensorI2C_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_CyBtldrCommStop(void)
{
    #if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            sensorI2C_I2CCyBtldrCommStop();
        }
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            sensorI2C_SpiCyBtldrCommStop();
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            sensorI2C_UartCyBtldrCommStop();
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            sensorI2C_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
        sensorI2C_I2CCyBtldrCommStop();

    #elif(sensorI2C_SCB_MODE_SPI_CONST_CFG)
        sensorI2C_SpiCyBtldrCommStop();

    #elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
        sensorI2C_UartCyBtldrCommStop();

    #elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
        sensorI2C_EzI2CCyBtldrCommStop();

    #else
        /* Unknown mode */

    #endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: sensorI2C_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_CyBtldrCommReset(void)
{
    #if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            sensorI2C_I2CCyBtldrCommReset();
        }
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            sensorI2C_SpiCyBtldrCommReset();
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            sensorI2C_UartCyBtldrCommReset();
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            sensorI2C_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
        sensorI2C_I2CCyBtldrCommReset();

    #elif(sensorI2C_SCB_MODE_SPI_CONST_CFG)
        sensorI2C_SpiCyBtldrCommReset();

    #elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
        sensorI2C_UartCyBtldrCommReset();

    #elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
        sensorI2C_EzI2CCyBtldrCommReset();

    #else
        /* Unknown mode */

    #endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: sensorI2C_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus sensorI2C_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = sensorI2C_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = sensorI2C_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            status = sensorI2C_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = sensorI2C_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
        status = sensorI2C_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(sensorI2C_SCB_MODE_SPI_CONST_CFG)
        status = sensorI2C_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
        status = sensorI2C_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
        status = sensorI2C_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: sensorI2C_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus sensorI2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = sensorI2C_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = sensorI2C_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            status = sensorI2C_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = sensorI2C_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
        status = sensorI2C_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(sensorI2C_SCB_MODE_SPI_CONST_CFG)
        status = sensorI2C_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
        status = sensorI2C_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
        status = sensorI2C_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (sensorI2C_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
