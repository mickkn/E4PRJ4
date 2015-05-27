/*******************************************************************************
* File Name: sensorI2C_PM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "sensorI2C.h"
#include "sensorI2C_PVT.h"

#if(sensorI2C_SCB_MODE_I2C_INC)
    #include "sensorI2C_I2C_PVT.h"
#endif /* (sensorI2C_SCB_MODE_I2C_INC) */

#if(sensorI2C_SCB_MODE_EZI2C_INC)
    #include "sensorI2C_EZI2C_PVT.h"
#endif /* (sensorI2C_SCB_MODE_EZI2C_INC) */

#if(sensorI2C_SCB_MODE_SPI_INC || sensorI2C_SCB_MODE_UART_INC)
    #include "sensorI2C_SPI_UART_PVT.h"
#endif /* (sensorI2C_SCB_MODE_SPI_INC || sensorI2C_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG || \
   (sensorI2C_SCB_MODE_I2C_CONST_CFG   && (!sensorI2C_I2C_WAKE_ENABLE_CONST))   || \
   (sensorI2C_SCB_MODE_EZI2C_CONST_CFG && (!sensorI2C_EZI2C_WAKE_ENABLE_CONST)) || \
   (sensorI2C_SCB_MODE_SPI_CONST_CFG   && (!sensorI2C_SPI_WAKE_ENABLE_CONST))   || \
   (sensorI2C_SCB_MODE_UART_CONST_CFG  && (!sensorI2C_UART_WAKE_ENABLE_CONST)))

    sensorI2C_BACKUP_STRUCT sensorI2C_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: sensorI2C_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_Sleep(void)
{
#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(sensorI2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            sensorI2C_I2CSaveConfig();
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            sensorI2C_EzI2CSaveConfig();
        }
    #if(!sensorI2C_CY_SCBIP_V1)
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            sensorI2C_SpiSaveConfig();
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            sensorI2C_UartSaveConfig();
        }
    #endif /* (!sensorI2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        sensorI2C_backup.enableState = (uint8) sensorI2C_GET_CTRL_ENABLED;

        if(0u != sensorI2C_backup.enableState)
        {
            sensorI2C_Stop();
        }
    }

#else

    #if (sensorI2C_SCB_MODE_I2C_CONST_CFG && sensorI2C_I2C_WAKE_ENABLE_CONST)
        sensorI2C_I2CSaveConfig();

    #elif (sensorI2C_SCB_MODE_EZI2C_CONST_CFG && sensorI2C_EZI2C_WAKE_ENABLE_CONST)
        sensorI2C_EzI2CSaveConfig();

    #elif (sensorI2C_SCB_MODE_SPI_CONST_CFG && sensorI2C_SPI_WAKE_ENABLE_CONST)
        sensorI2C_SpiSaveConfig();

    #elif (sensorI2C_SCB_MODE_UART_CONST_CFG && sensorI2C_UART_WAKE_ENABLE_CONST)
        sensorI2C_UartSaveConfig();

    #else

        sensorI2C_backup.enableState = (uint8) sensorI2C_GET_CTRL_ENABLED;

        if(0u != sensorI2C_backup.enableState)
        {
            sensorI2C_Stop();
        }

    #endif /* defined (sensorI2C_SCB_MODE_I2C_CONST_CFG) && (sensorI2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: sensorI2C_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_Wakeup(void)
{
#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(sensorI2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            sensorI2C_I2CRestoreConfig();
        }
        else if(sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            sensorI2C_EzI2CRestoreConfig();
        }
    #if(!sensorI2C_CY_SCBIP_V1)
        else if(sensorI2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            sensorI2C_SpiRestoreConfig();
        }
        else if(sensorI2C_SCB_MODE_UART_RUNTM_CFG)
        {
            sensorI2C_UartRestoreConfig();
        }
    #endif /* (!sensorI2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != sensorI2C_backup.enableState)
        {
            sensorI2C_Enable();
        }
    }

#else

    #if (sensorI2C_SCB_MODE_I2C_CONST_CFG  && sensorI2C_I2C_WAKE_ENABLE_CONST)
        sensorI2C_I2CRestoreConfig();

    #elif (sensorI2C_SCB_MODE_EZI2C_CONST_CFG && sensorI2C_EZI2C_WAKE_ENABLE_CONST)
        sensorI2C_EzI2CRestoreConfig();

    #elif (sensorI2C_SCB_MODE_SPI_CONST_CFG && sensorI2C_SPI_WAKE_ENABLE_CONST)
        sensorI2C_SpiRestoreConfig();

    #elif (sensorI2C_SCB_MODE_UART_CONST_CFG && sensorI2C_UART_WAKE_ENABLE_CONST)
        sensorI2C_UartRestoreConfig();

    #else

        if(0u != sensorI2C_backup.enableState)
        {
            sensorI2C_Enable();
        }

    #endif /* (sensorI2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
