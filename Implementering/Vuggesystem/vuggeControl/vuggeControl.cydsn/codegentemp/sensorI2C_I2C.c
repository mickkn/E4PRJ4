/*******************************************************************************
* File Name: sensorI2C_I2C.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "sensorI2C_PVT.h"
#include "sensorI2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 sensorI2C_state;  /* Current state of I2C FSM */

#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const sensorI2C_I2C_INIT_STRUCT sensorI2C_configI2C =
    {
        sensorI2C_I2C_MODE,
        sensorI2C_I2C_OVS_FACTOR_LOW,
        sensorI2C_I2C_OVS_FACTOR_HIGH,
        sensorI2C_I2C_MEDIAN_FILTER_ENABLE,
        sensorI2C_I2C_SLAVE_ADDRESS,
        sensorI2C_I2C_SLAVE_ADDRESS_MASK,
        sensorI2C_I2C_ACCEPT_ADDRESS,
        sensorI2C_I2C_WAKE_ENABLE,
        sensorI2C_I2C_BYTE_MODE_ENABLE,
        sensorI2C_I2C_DATA_RATE,
    };

    /*******************************************************************************
    * Function Name: sensorI2C_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void sensorI2C_I2CInit(const sensorI2C_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            sensorI2C_SetPins(sensorI2C_SCB_MODE_I2C, sensorI2C_DUMMY_PARAM,
                                                                    sensorI2C_DUMMY_PARAM);

            /* Store internal configuration */
            sensorI2C_scbMode       = (uint8) sensorI2C_SCB_MODE_I2C;
            sensorI2C_scbEnableWake = (uint8) config->enableWake;
            sensorI2C_scbEnableIntr = (uint8) sensorI2C_SCB_IRQ_INTERNAL;

            sensorI2C_mode          = (uint8) config->mode;
            sensorI2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (sensorI2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            sensorI2C_SET_I2C_CFG_SDA_FILT_TRIM(sensorI2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (sensorI2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((sensorI2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= sensorI2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (sensorI2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                sensorI2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = sensorI2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                sensorI2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = sensorI2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!sensorI2C_CY_SCBIP_V0)
            locEnableWake = (sensorI2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!sensorI2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            sensorI2C_CTRL_REG     = sensorI2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            sensorI2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            sensorI2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            sensorI2C_I2C_CTRL_REG = sensorI2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                                            sensorI2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)  |
                                            sensorI2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode)           |
                                            sensorI2C_I2C_CTRL;



            /* Configure RX direction */
            sensorI2C_RX_CTRL_REG      = sensorI2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                sensorI2C_I2C_RX_CTRL;
            sensorI2C_RX_FIFO_CTRL_REG = sensorI2C_CLEAR_REG;

            /* Set default address and mask */
            sensorI2C_RX_MATCH_REG    = ((sensorI2C_I2C_SLAVE) ?
                                                (sensorI2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 sensorI2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (sensorI2C_CLEAR_REG));


            /* Configure TX direction */
            sensorI2C_TX_CTRL_REG      = sensorI2C_I2C_TX_CTRL;
            sensorI2C_TX_FIFO_CTRL_REG = sensorI2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (sensorI2C_ISR_NUMBER);
            CyIntSetPriority(sensorI2C_ISR_NUMBER, sensorI2C_ISR_PRIORITY);
            (void) CyIntSetVector(sensorI2C_ISR_NUMBER, &sensorI2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!sensorI2C_CY_SCBIP_V1)
            sensorI2C_INTR_SPI_EC_MASK_REG = sensorI2C_NO_INTR_SOURCES;
        #endif /* (!sensorI2C_CY_SCBIP_V1) */

            sensorI2C_INTR_I2C_EC_MASK_REG = sensorI2C_NO_INTR_SOURCES;
            sensorI2C_INTR_RX_MASK_REG     = sensorI2C_NO_INTR_SOURCES;
            sensorI2C_INTR_TX_MASK_REG     = sensorI2C_NO_INTR_SOURCES;

            sensorI2C_INTR_SLAVE_MASK_REG  = ((sensorI2C_I2C_SLAVE) ?
                                                     (sensorI2C_I2C_INTR_SLAVE_MASK) :
                                                     (sensorI2C_CLEAR_REG));

            sensorI2C_INTR_MASTER_MASK_REG = ((sensorI2C_I2C_MASTER) ?
                                                     (sensorI2C_I2C_INTR_MASTER_MASK) :
                                                     (sensorI2C_CLEAR_REG));

            /* Configure global variables */
            sensorI2C_state = sensorI2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            sensorI2C_slStatus        = 0u;
            sensorI2C_slRdBufIndex    = 0u;
            sensorI2C_slWrBufIndex    = 0u;
            sensorI2C_slOverFlowCount = 0u;

            /* Internal master variables */
            sensorI2C_mstrStatus     = 0u;
            sensorI2C_mstrRdBufIndex = 0u;
            sensorI2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: sensorI2C_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void sensorI2C_I2CInit(void)
    {
    #if(sensorI2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        sensorI2C_SET_I2C_CFG_SDA_FILT_TRIM(sensorI2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (sensorI2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        sensorI2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        sensorI2C_CTRL_REG     = sensorI2C_I2C_DEFAULT_CTRL;
        sensorI2C_I2C_CTRL_REG = sensorI2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        sensorI2C_RX_CTRL_REG      = sensorI2C_I2C_DEFAULT_RX_CTRL;
        sensorI2C_RX_FIFO_CTRL_REG = sensorI2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        sensorI2C_RX_MATCH_REG     = sensorI2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        sensorI2C_TX_CTRL_REG      = sensorI2C_I2C_DEFAULT_TX_CTRL;
        sensorI2C_TX_FIFO_CTRL_REG = sensorI2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (sensorI2C_ISR_NUMBER);
        CyIntSetPriority(sensorI2C_ISR_NUMBER, sensorI2C_ISR_PRIORITY);
    #if(!sensorI2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(sensorI2C_ISR_NUMBER, &sensorI2C_I2C_ISR);
    #endif /* (sensorI2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!sensorI2C_CY_SCBIP_V1)
        sensorI2C_INTR_SPI_EC_MASK_REG = sensorI2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!sensorI2C_CY_SCBIP_V1) */

        sensorI2C_INTR_I2C_EC_MASK_REG = sensorI2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        sensorI2C_INTR_SLAVE_MASK_REG  = sensorI2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        sensorI2C_INTR_MASTER_MASK_REG = sensorI2C_I2C_DEFAULT_INTR_MASTER_MASK;
        sensorI2C_INTR_RX_MASK_REG     = sensorI2C_I2C_DEFAULT_INTR_RX_MASK;
        sensorI2C_INTR_TX_MASK_REG     = sensorI2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        sensorI2C_state = sensorI2C_I2C_FSM_IDLE;

    #if(sensorI2C_I2C_SLAVE)
        /* Internal slave variable */
        sensorI2C_slStatus        = 0u;
        sensorI2C_slRdBufIndex    = 0u;
        sensorI2C_slWrBufIndex    = 0u;
        sensorI2C_slOverFlowCount = 0u;
    #endif /* (sensorI2C_I2C_SLAVE) */

    #if(sensorI2C_I2C_MASTER)
    /* Internal master variable */
        sensorI2C_mstrStatus     = 0u;
        sensorI2C_mstrRdBufIndex = 0u;
        sensorI2C_mstrWrBufIndex = 0u;
    #endif /* (sensorI2C_I2C_MASTER) */
    }
#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: sensorI2C_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state and disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_I2CStop(void)
{
    /* Disable TX interrupt sources in order not to cause a false trigger.
    * The incoming transaction will enable an appropriate TX interrupt.
    */
    sensorI2C_SetTxInterruptMode(sensorI2C_NO_INTR_SOURCES);

#if(sensorI2C_CY_SCBIP_V0)
    /* Clear a pending interrupt as the TX FIFO becomes empty and the block does not gate
    * an interrupt trigger when disabled.
    */
    sensorI2C_ClearPendingInt();
#endif /* (sensorI2C_CY_SCBIP_V0) */

    sensorI2C_state = sensorI2C_I2C_FSM_IDLE;
}


#if(sensorI2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: sensorI2C_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables sensorI2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void sensorI2C_I2CSaveConfig(void)
    {
    #if (!sensorI2C_CY_SCBIP_V0)
        #if (sensorI2C_I2C_MULTI_MASTER_SLAVE_CONST && sensorI2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (sensorI2C_CTRL_REG & sensorI2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                sensorI2C_Stop();
                sensorI2C_CTRL_REG |= sensorI2C_CTRL_EC_AM_MODE;
                sensorI2C_Enable();
            }
        #endif /* (sensorI2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (sensorI2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            sensorI2C_SCBCLK_Stop();
        #endif /* (sensorI2C_SCB_CLK_INTERNAL) */
    #endif /* (!sensorI2C_CY_SCBIP_V0) */

        sensorI2C_SetI2CExtClkInterruptMode(sensorI2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: sensorI2C_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables sensorI2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void sensorI2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        sensorI2C_SetI2CExtClkInterruptMode(sensorI2C_NO_INTR_SOURCES);

    #if (!sensorI2C_CY_SCBIP_V0)
        #if (sensorI2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            sensorI2C_SCBCLK_Start();
        #endif /* (sensorI2C_SCB_CLK_INTERNAL) */
    #endif /* (!sensorI2C_CY_SCBIP_V0) */
    }
#endif /* (sensorI2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
