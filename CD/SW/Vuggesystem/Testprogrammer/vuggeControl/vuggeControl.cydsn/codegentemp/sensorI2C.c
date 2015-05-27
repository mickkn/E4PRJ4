/*******************************************************************************
* File Name: sensorI2C.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 sensorI2C_scbMode = sensorI2C_SCB_MODE_UNCONFIG;
    uint8 sensorI2C_scbEnableWake;
    uint8 sensorI2C_scbEnableIntr;

    /* I2C configuration variables */
    uint8 sensorI2C_mode;
    uint8 sensorI2C_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * sensorI2C_rxBuffer;
    uint8  sensorI2C_rxDataBits;
    uint32 sensorI2C_rxBufferSize;

    volatile uint8 * sensorI2C_txBuffer;
    uint8  sensorI2C_txDataBits;
    uint32 sensorI2C_txBufferSize;

    /* EZI2C configuration variables */
    uint8 sensorI2C_numberOfAddr;
    uint8 sensorI2C_subAddrSize;
#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 sensorI2C_initVar = 0u;

#if !defined (CY_REMOVE_sensorI2C_CUSTOM_INTR_HANDLER)
    cyisraddress sensorI2C_customIntrHandler = NULL;
#endif /* !defined (CY_REMOVE_sensorI2C_CUSTOM_INTR_HANDLER) */


/***************************************
*    Private Function Prototypes
***************************************/

static void sensorI2C_ScbEnableIntr(void);
static void sensorI2C_ScbModeStop(void);


/*******************************************************************************
* Function Name: sensorI2C_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_Init(void)
{
#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    if(sensorI2C_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        sensorI2C_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
    sensorI2C_I2CInit();

#elif(sensorI2C_SCB_MODE_SPI_CONST_CFG)
    sensorI2C_SpiInit();

#elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
    sensorI2C_UartInit();

#elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
    sensorI2C_EzI2CInit();

#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: sensorI2C_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_Enable(void)
{
#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if(!sensorI2C_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        sensorI2C_CTRL_REG |= sensorI2C_CTRL_ENABLED;

        sensorI2C_ScbEnableIntr();
    }
#else
    sensorI2C_CTRL_REG |= sensorI2C_CTRL_ENABLED;

    sensorI2C_ScbEnableIntr();
#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: sensorI2C_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  sensorI2C_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void sensorI2C_Start(void)
{
    if(0u == sensorI2C_initVar)
    {
        sensorI2C_Init();
        sensorI2C_initVar = 1u; /* Component was initialized */
    }

    sensorI2C_Enable();
}


/*******************************************************************************
* Function Name: sensorI2C_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_Stop(void)
{
#if(sensorI2C_SCB_IRQ_INTERNAL)
    sensorI2C_DisableInt();
#endif /* (sensorI2C_SCB_IRQ_INTERNAL) */

    sensorI2C_CTRL_REG &= (uint32) ~sensorI2C_CTRL_ENABLED;  /* Disable scb IP */

#if(sensorI2C_SCB_IRQ_INTERNAL)
    sensorI2C_ClearPendingInt();
#endif /* (sensorI2C_SCB_IRQ_INTERNAL) */

    sensorI2C_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: sensorI2C_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = sensorI2C_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~sensorI2C_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (sensorI2C_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    sensorI2C_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: sensorI2C_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = sensorI2C_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~sensorI2C_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (sensorI2C_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    sensorI2C_TX_FIFO_CTRL_REG = txFifoCtrl;
}


/*******************************************************************************
* Function Name: sensorI2C_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operation such as software buffer management functions
*  before the interrupt returns.  It is the user's responsibility not to break
*  the software buffer operations. Only one custom handler is supported, which
*  is the function provided by the most recent call.
*  At the initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void sensorI2C_SetCustomInterruptHandler(cyisraddress func)
{
#if !defined (CY_REMOVE_sensorI2C_CUSTOM_INTR_HANDLER)
    sensorI2C_customIntrHandler = func; /* Register interrupt handler */
#else
    if(NULL != func)
    {
        /* Suppress compiler warning */
    }
#endif /* !defined (CY_REMOVE_sensorI2C_CUSTOM_INTR_HANDLER) */
}


/*******************************************************************************
* Function Name: sensorI2C_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void sensorI2C_ScbEnableIntr(void)
{
#if(sensorI2C_SCB_IRQ_INTERNAL)
    #if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt in NVIC */
        if(0u != sensorI2C_scbEnableIntr)
        {
            sensorI2C_EnableInt();
        }
    #else
        sensorI2C_EnableInt();

    #endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (sensorI2C_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: sensorI2C_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void sensorI2C_ScbModeStop(void)
{
#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    if(sensorI2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        sensorI2C_I2CStop();
    }
    else if (sensorI2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        sensorI2C_EzI2CStop();
    }
#if (!sensorI2C_CY_SCBIP_V1)
    else if (sensorI2C_SCB_MODE_UART_RUNTM_CFG)
    {
        sensorI2C_UartStop();
    }
#endif /* (!sensorI2C_CY_SCBIP_V1) */
    else
    {
        /* Do nothing for other modes */
    }
#elif(sensorI2C_SCB_MODE_I2C_CONST_CFG)
    sensorI2C_I2CStop();

#elif(sensorI2C_SCB_MODE_EZI2C_CONST_CFG)
    sensorI2C_EzI2CStop();

#elif(sensorI2C_SCB_MODE_UART_CONST_CFG)
    sensorI2C_UartStop();

#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: sensorI2C_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void sensorI2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [sensorI2C_SCB_PINS_NUMBER];
        uint32 pinsDm   [sensorI2C_SCB_PINS_NUMBER];

    #if (!sensorI2C_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!sensorI2C_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for(i = 0u; i < sensorI2C_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = sensorI2C_HSIOM_DEF_SEL;
            pinsDm[i]    = sensorI2C_PIN_DM_ALG_HIZ;
        }

        if((sensorI2C_SCB_MODE_I2C   == mode) ||
           (sensorI2C_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_HSIOM_I2C_SEL;
            hsiomSel[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_HSIOM_I2C_SEL;

            pinsDm[sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_PIN_DM_OD_LO;
            pinsDm[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_PIN_DM_OD_LO;
        }
    #if (!sensorI2C_CY_SCBIP_V1)
        else if(sensorI2C_SCB_MODE_SPI == mode)
        {
            hsiomSel[sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
            hsiomSel[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
            hsiomSel[sensorI2C_SCLK_PIN_INDEX]        = sensorI2C_HSIOM_SPI_SEL;

            if(sensorI2C_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_PIN_DM_DIG_HIZ;
                pinsDm[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;
                pinsDm[sensorI2C_SCLK_PIN_INDEX]        = sensorI2C_PIN_DM_DIG_HIZ;

            #if(sensorI2C_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[sensorI2C_SS0_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
                pinsDm  [sensorI2C_SS0_PIN_INDEX] = sensorI2C_PIN_DM_DIG_HIZ;
            #endif /* (sensorI2C_SS1_PIN) */

            #if(sensorI2C_MISO_SDA_TX_PIN)
                /* Disable input buffer */
                 pinsInBuf |= sensorI2C_MISO_SDA_TX_PIN_MASK;
            #endif /* (sensorI2C_MISO_SDA_TX_PIN_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;
                pinsDm[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_PIN_DM_DIG_HIZ;
                pinsDm[sensorI2C_SCLK_PIN_INDEX]        = sensorI2C_PIN_DM_STRONG;

            #if(sensorI2C_SS0_PIN)
                hsiomSel [sensorI2C_SS0_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
                pinsDm   [sensorI2C_SS0_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;
                pinsInBuf                                |= sensorI2C_SS0_PIN_MASK;
            #endif /* (sensorI2C_SS0_PIN) */

            #if(sensorI2C_SS1_PIN)
                hsiomSel [sensorI2C_SS1_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
                pinsDm   [sensorI2C_SS1_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;
                pinsInBuf                                |= sensorI2C_SS1_PIN_MASK;
            #endif /* (sensorI2C_SS1_PIN) */

            #if(sensorI2C_SS2_PIN)
                hsiomSel [sensorI2C_SS2_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
                pinsDm   [sensorI2C_SS2_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;
                pinsInBuf                                |= sensorI2C_SS2_PIN_MASK;
            #endif /* (sensorI2C_SS2_PIN) */

            #if(sensorI2C_SS3_PIN)
                hsiomSel [sensorI2C_SS3_PIN_INDEX] = sensorI2C_HSIOM_SPI_SEL;
                pinsDm   [sensorI2C_SS3_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;
                pinsInBuf                                |= sensorI2C_SS3_PIN_MASK;
            #endif /* (sensorI2C_SS2_PIN) */

                /* Disable input buffers */
            #if(sensorI2C_MOSI_SCL_RX_PIN)
                pinsInBuf |= sensorI2C_MOSI_SCL_RX_PIN_MASK;
            #endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

             #if(sensorI2C_MOSI_SCL_RX_WAKE_PIN)
                pinsInBuf |= sensorI2C_MOSI_SCL_RX_WAKE_PIN_MASK;
            #endif /* (sensorI2C_MOSI_SCL_RX_WAKE_PIN) */

            #if(sensorI2C_SCLK_PIN)
                pinsInBuf |= sensorI2C_SCLK_PIN_MASK;
            #endif /* (sensorI2C_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if(sensorI2C_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_HSIOM_UART_SEL;
                pinsDm  [sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (sensorI2C_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_HSIOM_UART_SEL;
                    pinsDm  [sensorI2C_MOSI_SCL_RX_PIN_INDEX] = sensorI2C_PIN_DM_DIG_HIZ;
                }

                if(0u != (sensorI2C_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_HSIOM_UART_SEL;
                    pinsDm  [sensorI2C_MISO_SDA_TX_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;

                #if(sensorI2C_MISO_SDA_TX_PIN)
                     pinsInBuf |= sensorI2C_MISO_SDA_TX_PIN_MASK;
                #endif /* (sensorI2C_MISO_SDA_TX_PIN_PIN) */
                }

            #if !(sensorI2C_CY_SCBIP_V0 || sensorI2C_CY_SCBIP_V1)
                if(sensorI2C_UART_MODE_STD == subMode)
                {
                    if(0u != (sensorI2C_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[sensorI2C_SCLK_PIN_INDEX] = sensorI2C_HSIOM_UART_SEL;
                        pinsDm  [sensorI2C_SCLK_PIN_INDEX] = sensorI2C_PIN_DM_DIG_HIZ;
                    }

                    if(0u != (sensorI2C_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[sensorI2C_SS0_PIN_INDEX] = sensorI2C_HSIOM_UART_SEL;
                        pinsDm  [sensorI2C_SS0_PIN_INDEX] = sensorI2C_PIN_DM_STRONG;

                    #if(sensorI2C_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= sensorI2C_SS0_PIN_MASK;
                    #endif /* (sensorI2C_SS0_PIN) */
                    }
                }
            #endif /* !(sensorI2C_CY_SCBIP_V0 || sensorI2C_CY_SCBIP_V1) */
            }
        }
    #endif /* (!sensorI2C_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if(sensorI2C_MOSI_SCL_RX_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_MOSI_SCL_RX_HSIOM_REG,
                                       sensorI2C_MOSI_SCL_RX_HSIOM_MASK,
                                       sensorI2C_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[sensorI2C_MOSI_SCL_RX_PIN_INDEX]);

        sensorI2C_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8) pinsDm[sensorI2C_MOSI_SCL_RX_PIN_INDEX]);

    #if (!sensorI2C_CY_SCBIP_V1)
        sensorI2C_SET_INP_DIS(sensorI2C_spi_mosi_i2c_scl_uart_rx_INP_DIS,
                                     sensorI2C_spi_mosi_i2c_scl_uart_rx_MASK,
                                     (0u != (pinsInBuf & sensorI2C_MOSI_SCL_RX_PIN_MASK)));
    #endif /* (!sensorI2C_CY_SCBIP_V1) */
    #endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

    #if(sensorI2C_MOSI_SCL_RX_WAKE_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[sensorI2C_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        sensorI2C_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[sensorI2C_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        sensorI2C_SET_INP_DIS(sensorI2C_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS,
                                     sensorI2C_spi_mosi_i2c_scl_uart_rx_wake_MASK,
                                     (0u != (pinsInBuf & sensorI2C_MOSI_SCL_RX_WAKE_PIN_MASK)));

         /* Set interrupt on falling edge */
        sensorI2C_SET_INCFG_TYPE(sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                        sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                        sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                        sensorI2C_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (sensorI2C_MOSI_SCL_RX_WAKE_PIN) */

    #if(sensorI2C_MISO_SDA_TX_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_MISO_SDA_TX_HSIOM_REG,
                                       sensorI2C_MISO_SDA_TX_HSIOM_MASK,
                                       sensorI2C_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[sensorI2C_MISO_SDA_TX_PIN_INDEX]);

        sensorI2C_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8) pinsDm[sensorI2C_MISO_SDA_TX_PIN_INDEX]);

    #if (!sensorI2C_CY_SCBIP_V1)
        sensorI2C_SET_INP_DIS(sensorI2C_spi_miso_i2c_sda_uart_tx_INP_DIS,
                                     sensorI2C_spi_miso_i2c_sda_uart_tx_MASK,
                                    (0u != (pinsInBuf & sensorI2C_MISO_SDA_TX_PIN_MASK)));
    #endif /* (!sensorI2C_CY_SCBIP_V1) */
    #endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

    #if(sensorI2C_SCLK_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_SCLK_HSIOM_REG, sensorI2C_SCLK_HSIOM_MASK,
                                       sensorI2C_SCLK_HSIOM_POS, hsiomSel[sensorI2C_SCLK_PIN_INDEX]);

        sensorI2C_spi_sclk_SetDriveMode((uint8) pinsDm[sensorI2C_SCLK_PIN_INDEX]);

        sensorI2C_SET_INP_DIS(sensorI2C_spi_sclk_INP_DIS,
                                     sensorI2C_spi_sclk_MASK,
                                     (0u != (pinsInBuf & sensorI2C_SCLK_PIN_MASK)));
    #endif /* (sensorI2C_SCLK_PIN) */

    #if(sensorI2C_SS0_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_SS0_HSIOM_REG, sensorI2C_SS0_HSIOM_MASK,
                                       sensorI2C_SS0_HSIOM_POS, hsiomSel[sensorI2C_SS0_PIN_INDEX]);

        sensorI2C_spi_ss0_SetDriveMode((uint8) pinsDm[sensorI2C_SS0_PIN_INDEX]);

        sensorI2C_SET_INP_DIS(sensorI2C_spi_ss0_INP_DIS,
                                     sensorI2C_spi_ss0_MASK,
                                     (0u != (pinsInBuf & sensorI2C_SS0_PIN_MASK)));
    #endif /* (sensorI2C_SS1_PIN) */

    #if(sensorI2C_SS1_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_SS1_HSIOM_REG, sensorI2C_SS1_HSIOM_MASK,
                                       sensorI2C_SS1_HSIOM_POS, hsiomSel[sensorI2C_SS1_PIN_INDEX]);

        sensorI2C_spi_ss1_SetDriveMode((uint8) pinsDm[sensorI2C_SS1_PIN_INDEX]);

        sensorI2C_SET_INP_DIS(sensorI2C_spi_ss1_INP_DIS,
                                     sensorI2C_spi_ss1_MASK,
                                     (0u != (pinsInBuf & sensorI2C_SS1_PIN_MASK)));
    #endif /* (sensorI2C_SS1_PIN) */

    #if(sensorI2C_SS2_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_SS2_HSIOM_REG, sensorI2C_SS2_HSIOM_MASK,
                                       sensorI2C_SS2_HSIOM_POS, hsiomSel[sensorI2C_SS2_PIN_INDEX]);

        sensorI2C_spi_ss2_SetDriveMode((uint8) pinsDm[sensorI2C_SS2_PIN_INDEX]);

        sensorI2C_SET_INP_DIS(sensorI2C_spi_ss2_INP_DIS,
                                     sensorI2C_spi_ss2_MASK,
                                     (0u != (pinsInBuf & sensorI2C_SS2_PIN_MASK)));
    #endif /* (sensorI2C_SS2_PIN) */

    #if(sensorI2C_SS3_PIN)
        sensorI2C_SET_HSIOM_SEL(sensorI2C_SS3_HSIOM_REG,  sensorI2C_SS3_HSIOM_MASK,
                                       sensorI2C_SS3_HSIOM_POS, hsiomSel[sensorI2C_SS3_PIN_INDEX]);

        sensorI2C_spi_ss3_SetDriveMode((uint8) pinsDm[sensorI2C_SS3_PIN_INDEX]);

        sensorI2C_SET_INP_DIS(sensorI2C_spi_ss3_INP_DIS,
                                     sensorI2C_spi_ss3_MASK,
                                     (0u != (pinsInBuf & sensorI2C_SS3_PIN_MASK)));
    #endif /* (sensorI2C_SS3_PIN) */
    }

#endif /* (sensorI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (sensorI2C_CY_SCBIP_V0 || sensorI2C_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: sensorI2C_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void sensorI2C_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (sensorI2C_CTRL_REG & sensorI2C_CTRL_EC_AM_MODE)) &&
            (0u == (sensorI2C_I2C_CTRL_REG & sensorI2C_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            sensorI2C_CTRL_REG &= ~sensorI2C_CTRL_EC_AM_MODE;
            sensorI2C_CTRL_REG |=  sensorI2C_CTRL_EC_AM_MODE;
        }

        sensorI2C_I2C_SLAVE_CMD_REG = sensorI2C_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (sensorI2C_CY_SCBIP_V0 || sensorI2C_CY_SCBIP_V1) */


/* [] END OF FILE */
