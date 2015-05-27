/*******************************************************************************
* File Name: debugOut.c
* Version 2.40
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "debugOut.h"
#if (debugOut_INTERNAL_CLOCK_USED)
    #include "debugOut_IntClock.h"
#endif /* End debugOut_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 debugOut_initVar = 0u;

#if (debugOut_TX_INTERRUPT_ENABLED && debugOut_TX_ENABLED)
    volatile uint8 debugOut_txBuffer[debugOut_TX_BUFFER_SIZE];
    volatile uint8 debugOut_txBufferRead = 0u;
    uint8 debugOut_txBufferWrite = 0u;
#endif /* (debugOut_TX_INTERRUPT_ENABLED && debugOut_TX_ENABLED) */

#if (debugOut_RX_INTERRUPT_ENABLED && (debugOut_RX_ENABLED || debugOut_HD_ENABLED))
    uint8 debugOut_errorStatus = 0u;
    volatile uint8 debugOut_rxBuffer[debugOut_RX_BUFFER_SIZE];
    volatile uint8 debugOut_rxBufferRead  = 0u;
    volatile uint8 debugOut_rxBufferWrite = 0u;
    volatile uint8 debugOut_rxBufferLoopDetect = 0u;
    volatile uint8 debugOut_rxBufferOverflow   = 0u;
    #if (debugOut_RXHW_ADDRESS_ENABLED)
        volatile uint8 debugOut_rxAddressMode = debugOut_RX_ADDRESS_MODE;
        volatile uint8 debugOut_rxAddressDetected = 0u;
    #endif /* (debugOut_RXHW_ADDRESS_ENABLED) */
#endif /* (debugOut_RX_INTERRUPT_ENABLED && (debugOut_RX_ENABLED || debugOut_HD_ENABLED)) */


/*******************************************************************************
* Function Name: debugOut_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  debugOut_Start() sets the initVar variable, calls the
*  debugOut_Init() function, and then calls the
*  debugOut_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The debugOut_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time debugOut_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the debugOut_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void debugOut_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(debugOut_initVar == 0u)
    {
        debugOut_Init();
        debugOut_initVar = 1u;
    }

    debugOut_Enable();
}


/*******************************************************************************
* Function Name: debugOut_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call debugOut_Init() because
*  the debugOut_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void debugOut_Init(void) 
{
    #if(debugOut_RX_ENABLED || debugOut_HD_ENABLED)

        #if (debugOut_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(debugOut_RX_VECT_NUM, &debugOut_RXISR);
            CyIntSetPriority(debugOut_RX_VECT_NUM, debugOut_RX_PRIOR_NUM);
            debugOut_errorStatus = 0u;
        #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

        #if (debugOut_RXHW_ADDRESS_ENABLED)
            debugOut_SetRxAddressMode(debugOut_RX_ADDRESS_MODE);
            debugOut_SetRxAddress1(debugOut_RX_HW_ADDRESS1);
            debugOut_SetRxAddress2(debugOut_RX_HW_ADDRESS2);
        #endif /* End debugOut_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        debugOut_RXBITCTR_PERIOD_REG = debugOut_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        debugOut_RXSTATUS_MASK_REG  = debugOut_INIT_RX_INTERRUPTS_MASK;
    #endif /* End debugOut_RX_ENABLED || debugOut_HD_ENABLED*/

    #if(debugOut_TX_ENABLED)
        #if (debugOut_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(debugOut_TX_VECT_NUM, &debugOut_TXISR);
            CyIntSetPriority(debugOut_TX_VECT_NUM, debugOut_TX_PRIOR_NUM);
        #endif /* (debugOut_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (debugOut_TXCLKGEN_DP)
            debugOut_TXBITCLKGEN_CTR_REG = debugOut_BIT_CENTER;
            debugOut_TXBITCLKTX_COMPLETE_REG = ((debugOut_NUMBER_OF_DATA_BITS +
                        debugOut_NUMBER_OF_START_BIT) * debugOut_OVER_SAMPLE_COUNT) - 1u;
        #else
            debugOut_TXBITCTR_PERIOD_REG = ((debugOut_NUMBER_OF_DATA_BITS +
                        debugOut_NUMBER_OF_START_BIT) * debugOut_OVER_SAMPLE_8) - 1u;
        #endif /* End debugOut_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (debugOut_TX_INTERRUPT_ENABLED)
            debugOut_TXSTATUS_MASK_REG = debugOut_TX_STS_FIFO_EMPTY;
        #else
            debugOut_TXSTATUS_MASK_REG = debugOut_INIT_TX_INTERRUPTS_MASK;
        #endif /*End debugOut_TX_INTERRUPT_ENABLED*/

    #endif /* End debugOut_TX_ENABLED */

    #if(debugOut_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        debugOut_WriteControlRegister( \
            (debugOut_ReadControlRegister() & (uint8)~debugOut_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(debugOut_PARITY_TYPE << debugOut_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End debugOut_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: debugOut_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call debugOut_Enable() because the debugOut_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  debugOut_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void debugOut_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (debugOut_RX_ENABLED || debugOut_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        debugOut_RXBITCTR_CONTROL_REG |= debugOut_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        debugOut_RXSTATUS_ACTL_REG  |= debugOut_INT_ENABLE;

        #if (debugOut_RX_INTERRUPT_ENABLED)
            debugOut_EnableRxInt();

            #if (debugOut_RXHW_ADDRESS_ENABLED)
                debugOut_rxAddressDetected = 0u;
            #endif /* (debugOut_RXHW_ADDRESS_ENABLED) */
        #endif /* (debugOut_RX_INTERRUPT_ENABLED) */
    #endif /* (debugOut_RX_ENABLED || debugOut_HD_ENABLED) */

    #if(debugOut_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!debugOut_TXCLKGEN_DP)
            debugOut_TXBITCTR_CONTROL_REG |= debugOut_CNTR_ENABLE;
        #endif /* End debugOut_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        debugOut_TXSTATUS_ACTL_REG |= debugOut_INT_ENABLE;
        #if (debugOut_TX_INTERRUPT_ENABLED)
            debugOut_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            debugOut_EnableTxInt();
        #endif /* (debugOut_TX_INTERRUPT_ENABLED) */
     #endif /* (debugOut_TX_INTERRUPT_ENABLED) */

    #if (debugOut_INTERNAL_CLOCK_USED)
        debugOut_IntClock_Start();  /* Enable the clock */
    #endif /* (debugOut_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: debugOut_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void debugOut_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (debugOut_RX_ENABLED || debugOut_HD_ENABLED)
        debugOut_RXBITCTR_CONTROL_REG &= (uint8) ~debugOut_CNTR_ENABLE;
    #endif /* (debugOut_RX_ENABLED || debugOut_HD_ENABLED) */

    #if (debugOut_TX_ENABLED)
        #if(!debugOut_TXCLKGEN_DP)
            debugOut_TXBITCTR_CONTROL_REG &= (uint8) ~debugOut_CNTR_ENABLE;
        #endif /* (!debugOut_TXCLKGEN_DP) */
    #endif /* (debugOut_TX_ENABLED) */

    #if (debugOut_INTERNAL_CLOCK_USED)
        debugOut_IntClock_Stop();   /* Disable the clock */
    #endif /* (debugOut_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (debugOut_RX_ENABLED || debugOut_HD_ENABLED)
        debugOut_RXSTATUS_ACTL_REG  &= (uint8) ~debugOut_INT_ENABLE;

        #if (debugOut_RX_INTERRUPT_ENABLED)
            debugOut_DisableRxInt();
        #endif /* (debugOut_RX_INTERRUPT_ENABLED) */
    #endif /* (debugOut_RX_ENABLED || debugOut_HD_ENABLED) */

    #if (debugOut_TX_ENABLED)
        debugOut_TXSTATUS_ACTL_REG &= (uint8) ~debugOut_INT_ENABLE;

        #if (debugOut_TX_INTERRUPT_ENABLED)
            debugOut_DisableTxInt();
        #endif /* (debugOut_TX_INTERRUPT_ENABLED) */
    #endif /* (debugOut_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: debugOut_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 debugOut_ReadControlRegister(void) 
{
    #if (debugOut_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(debugOut_CONTROL_REG);
    #endif /* (debugOut_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: debugOut_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  debugOut_WriteControlRegister(uint8 control) 
{
    #if (debugOut_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       debugOut_CONTROL_REG = control;
    #endif /* (debugOut_CONTROL_REG_REMOVED) */
}


#if(debugOut_RX_ENABLED || debugOut_HD_ENABLED)
    /*******************************************************************************
    * Function Name: debugOut_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      debugOut_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      debugOut_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      debugOut_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      debugOut_RX_STS_BREAK            Interrupt on break.
    *      debugOut_RX_STS_OVERRUN          Interrupt on overrun error.
    *      debugOut_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      debugOut_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void debugOut_SetRxInterruptMode(uint8 intSrc) 
    {
        debugOut_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: debugOut_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  debugOut_rxBuffer - RAM buffer pointer for save received data.
    *  debugOut_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  debugOut_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  debugOut_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 debugOut_ReadRxData(void) 
    {
        uint8 rxData;

    #if (debugOut_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        debugOut_DisableRxInt();

        locRxBufferRead  = debugOut_rxBufferRead;
        locRxBufferWrite = debugOut_rxBufferWrite;

        if( (debugOut_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = debugOut_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= debugOut_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            debugOut_rxBufferRead = locRxBufferRead;

            if(debugOut_rxBufferLoopDetect != 0u)
            {
                debugOut_rxBufferLoopDetect = 0u;
                #if ((debugOut_RX_INTERRUPT_ENABLED) && (debugOut_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( debugOut_HD_ENABLED )
                        if((debugOut_CONTROL_REG & debugOut_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            debugOut_RXSTATUS_MASK_REG  |= debugOut_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        debugOut_RXSTATUS_MASK_REG  |= debugOut_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end debugOut_HD_ENABLED */
                #endif /* ((debugOut_RX_INTERRUPT_ENABLED) && (debugOut_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = debugOut_RXDATA_REG;
        }

        debugOut_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = debugOut_RXDATA_REG;

    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: debugOut_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  debugOut_RX_STS_FIFO_NOTEMPTY.
    *  debugOut_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  debugOut_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   debugOut_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   debugOut_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 debugOut_ReadRxStatus(void) 
    {
        uint8 status;

        status = debugOut_RXSTATUS_REG & debugOut_RX_HW_MASK;

    #if (debugOut_RX_INTERRUPT_ENABLED)
        if(debugOut_rxBufferOverflow != 0u)
        {
            status |= debugOut_RX_STS_SOFT_BUFF_OVER;
            debugOut_rxBufferOverflow = 0u;
        }
    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: debugOut_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. debugOut_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  debugOut_rxBuffer - RAM buffer pointer for save received data.
    *  debugOut_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  debugOut_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  debugOut_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 debugOut_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (debugOut_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        debugOut_DisableRxInt();

        locRxBufferRead  = debugOut_rxBufferRead;
        locRxBufferWrite = debugOut_rxBufferWrite;

        if( (debugOut_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = debugOut_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= debugOut_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            debugOut_rxBufferRead = locRxBufferRead;

            if(debugOut_rxBufferLoopDetect != 0u)
            {
                debugOut_rxBufferLoopDetect = 0u;
                #if( (debugOut_RX_INTERRUPT_ENABLED) && (debugOut_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( debugOut_HD_ENABLED )
                        if((debugOut_CONTROL_REG & debugOut_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            debugOut_RXSTATUS_MASK_REG |= debugOut_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        debugOut_RXSTATUS_MASK_REG |= debugOut_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end debugOut_HD_ENABLED */
                #endif /* debugOut_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = debugOut_RXSTATUS_REG;
            if((rxStatus & debugOut_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = debugOut_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (debugOut_RX_STS_BREAK | debugOut_RX_STS_PAR_ERROR |
                                debugOut_RX_STS_STOP_ERROR | debugOut_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        debugOut_EnableRxInt();

    #else

        rxStatus =debugOut_RXSTATUS_REG;
        if((rxStatus & debugOut_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = debugOut_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (debugOut_RX_STS_BREAK | debugOut_RX_STS_PAR_ERROR |
                            debugOut_RX_STS_STOP_ERROR | debugOut_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: debugOut_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 debugOut_GetByte(void) 
    {
        
    #if (debugOut_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        debugOut_DisableRxInt();
        locErrorStatus = (uint16)debugOut_errorStatus;
        debugOut_errorStatus = 0u;
        debugOut_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | debugOut_ReadRxData() );
    #else
        return ( ((uint16)debugOut_ReadRxStatus() << 8u) | debugOut_ReadRxData() );
    #endif /* debugOut_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: debugOut_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  debugOut_rxBufferWrite - used to calculate left bytes.
    *  debugOut_rxBufferRead - used to calculate left bytes.
    *  debugOut_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 debugOut_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (debugOut_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        debugOut_DisableRxInt();

        if(debugOut_rxBufferRead == debugOut_rxBufferWrite)
        {
            if(debugOut_rxBufferLoopDetect != 0u)
            {
                size = debugOut_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(debugOut_rxBufferRead < debugOut_rxBufferWrite)
        {
            size = (debugOut_rxBufferWrite - debugOut_rxBufferRead);
        }
        else
        {
            size = (debugOut_RX_BUFFER_SIZE - debugOut_rxBufferRead) + debugOut_rxBufferWrite;
        }

        debugOut_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((debugOut_RXSTATUS_REG & debugOut_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: debugOut_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_rxBufferWrite - cleared to zero.
    *  debugOut_rxBufferRead - cleared to zero.
    *  debugOut_rxBufferLoopDetect - cleared to zero.
    *  debugOut_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void debugOut_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        debugOut_RXDATA_AUX_CTL_REG |= (uint8)  debugOut_RX_FIFO_CLR;
        debugOut_RXDATA_AUX_CTL_REG &= (uint8) ~debugOut_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (debugOut_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        debugOut_DisableRxInt();

        debugOut_rxBufferRead = 0u;
        debugOut_rxBufferWrite = 0u;
        debugOut_rxBufferLoopDetect = 0u;
        debugOut_rxBufferOverflow = 0u;

        debugOut_EnableRxInt();

    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: debugOut_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  debugOut__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  debugOut__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  debugOut__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  debugOut__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  debugOut__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  debugOut_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void debugOut_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(debugOut_RXHW_ADDRESS_ENABLED)
            #if(debugOut_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* debugOut_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = debugOut_CONTROL_REG & (uint8)~debugOut_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << debugOut_CTRL_RXADDR_MODE0_SHIFT);
                debugOut_CONTROL_REG = tmpCtrl;

                #if(debugOut_RX_INTERRUPT_ENABLED && \
                   (debugOut_RXBUFFERSIZE > debugOut_FIFO_LENGTH) )
                    debugOut_rxAddressMode = addressMode;
                    debugOut_rxAddressDetected = 0u;
                #endif /* End debugOut_RXBUFFERSIZE > debugOut_FIFO_LENGTH*/
            #endif /* End debugOut_CONTROL_REG_REMOVED */
        #else /* debugOut_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End debugOut_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: debugOut_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void debugOut_SetRxAddress1(uint8 address) 
    {
        debugOut_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: debugOut_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void debugOut_SetRxAddress2(uint8 address) 
    {
        debugOut_RXADDRESS2_REG = address;
    }

#endif  /* debugOut_RX_ENABLED || debugOut_HD_ENABLED*/


#if( (debugOut_TX_ENABLED) || (debugOut_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: debugOut_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   debugOut_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   debugOut_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   debugOut_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   debugOut_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void debugOut_SetTxInterruptMode(uint8 intSrc) 
    {
        debugOut_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: debugOut_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  debugOut_txBuffer - RAM buffer pointer for save data for transmission
    *  debugOut_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  debugOut_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  debugOut_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void debugOut_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(debugOut_initVar != 0u)
        {
        #if (debugOut_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            debugOut_DisableTxInt();

            if( (debugOut_txBufferRead == debugOut_txBufferWrite) &&
                ((debugOut_TXSTATUS_REG & debugOut_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                debugOut_TXDATA_REG = txDataByte;
            }
            else
            {
                if(debugOut_txBufferWrite >= debugOut_TX_BUFFER_SIZE)
                {
                    debugOut_txBufferWrite = 0u;
                }

                debugOut_txBuffer[debugOut_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                debugOut_txBufferWrite++;
            }

            debugOut_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            debugOut_TXDATA_REG = txDataByte;

        #endif /*(debugOut_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: debugOut_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 debugOut_ReadTxStatus(void) 
    {
        return(debugOut_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: debugOut_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_txBuffer - RAM buffer pointer for save data for transmission
    *  debugOut_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  debugOut_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  debugOut_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void debugOut_PutChar(uint8 txDataByte) 
    {
    #if (debugOut_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((debugOut_TX_BUFFER_SIZE > debugOut_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            debugOut_DisableTxInt();
        #endif /* (debugOut_TX_BUFFER_SIZE > 255) */

            locTxBufferWrite = debugOut_txBufferWrite;
            locTxBufferRead  = debugOut_txBufferRead;

        #if ((debugOut_TX_BUFFER_SIZE > debugOut_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            debugOut_EnableTxInt();
        #endif /* (debugOut_TX_BUFFER_SIZE > 255) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(debugOut_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((debugOut_TXSTATUS_REG & debugOut_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            debugOut_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= debugOut_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            debugOut_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((debugOut_TX_BUFFER_SIZE > debugOut_MAX_BYTE_VALUE) && (CY_PSOC3))
            debugOut_DisableTxInt();
        #endif /* (debugOut_TX_BUFFER_SIZE > 255) */

            debugOut_txBufferWrite = locTxBufferWrite;

        #if ((debugOut_TX_BUFFER_SIZE > debugOut_MAX_BYTE_VALUE) && (CY_PSOC3))
            debugOut_EnableTxInt();
        #endif /* (debugOut_TX_BUFFER_SIZE > 255) */

            if(0u != (debugOut_TXSTATUS_REG & debugOut_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                debugOut_SetPendingTxInt();
            }
        }

    #else

        while((debugOut_TXSTATUS_REG & debugOut_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        debugOut_TXDATA_REG = txDataByte;

    #endif /* End (debugOut_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: debugOut_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void debugOut_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(debugOut_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                debugOut_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: debugOut_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void debugOut_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(debugOut_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                debugOut_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: debugOut_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void debugOut_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(debugOut_initVar != 0u)
        {
            debugOut_PutChar(txDataByte);
            debugOut_PutChar(0x0Du);
            debugOut_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: debugOut_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not take to account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  debugOut_txBufferWrite - used to calculate left space.
    *  debugOut_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 debugOut_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (debugOut_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        debugOut_DisableTxInt();

        if(debugOut_txBufferRead == debugOut_txBufferWrite)
        {
            size = 0u;
        }
        else if(debugOut_txBufferRead < debugOut_txBufferWrite)
        {
            size = (debugOut_txBufferWrite - debugOut_txBufferRead);
        }
        else
        {
            size = (debugOut_TX_BUFFER_SIZE - debugOut_txBufferRead) +
                    debugOut_txBufferWrite;
        }

        debugOut_EnableTxInt();

    #else

        size = debugOut_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & debugOut_TX_STS_FIFO_FULL) != 0u)
        {
            size = debugOut_FIFO_LENGTH;
        }
        else if((size & debugOut_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (debugOut_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: debugOut_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_txBufferWrite - cleared to zero.
    *  debugOut_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void debugOut_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        debugOut_TXDATA_AUX_CTL_REG |= (uint8)  debugOut_TX_FIFO_CLR;
        debugOut_TXDATA_AUX_CTL_REG &= (uint8) ~debugOut_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (debugOut_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        debugOut_DisableTxInt();

        debugOut_txBufferRead = 0u;
        debugOut_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        debugOut_EnableTxInt();

    #endif /* (debugOut_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: debugOut_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   debugOut_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   debugOut_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   debugOut_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   debugOut_SEND_WAIT_REINIT - Performs both options: 
    *      debugOut_SEND_BREAK and debugOut_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with debugOut_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The debugOut_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void debugOut_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(debugOut_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(debugOut_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == debugOut_SEND_BREAK) ||
                (retMode == debugOut_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                debugOut_WriteControlRegister(debugOut_ReadControlRegister() |
                                                      debugOut_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                debugOut_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = debugOut_TXSTATUS_REG;
                }
                while((tmpStat & debugOut_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == debugOut_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == debugOut_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = debugOut_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & debugOut_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == debugOut_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == debugOut_REINIT) ||
                (retMode == debugOut_SEND_WAIT_REINIT) )
            {
                debugOut_WriteControlRegister(debugOut_ReadControlRegister() &
                                              (uint8)~debugOut_CTRL_HD_SEND_BREAK);
            }

        #else /* debugOut_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == debugOut_SEND_BREAK) ||
                (retMode == debugOut_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (debugOut_PARITY_TYPE != debugOut__B_UART__NONE_REVB) || \
                                    (debugOut_PARITY_TYPE_SW != 0u) )
                    debugOut_WriteControlRegister(debugOut_ReadControlRegister() |
                                                          debugOut_CTRL_HD_SEND_BREAK);
                #endif /* End debugOut_PARITY_TYPE != debugOut__B_UART__NONE_REVB  */

                #if(debugOut_TXCLKGEN_DP)
                    txPeriod = debugOut_TXBITCLKTX_COMPLETE_REG;
                    debugOut_TXBITCLKTX_COMPLETE_REG = debugOut_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = debugOut_TXBITCTR_PERIOD_REG;
                    debugOut_TXBITCTR_PERIOD_REG = debugOut_TXBITCTR_BREAKBITS8X;
                #endif /* End debugOut_TXCLKGEN_DP */

                /* Send zeros */
                debugOut_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = debugOut_TXSTATUS_REG;
                }
                while((tmpStat & debugOut_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == debugOut_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == debugOut_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = debugOut_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & debugOut_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == debugOut_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == debugOut_REINIT) ||
                (retMode == debugOut_SEND_WAIT_REINIT) )
            {

            #if(debugOut_TXCLKGEN_DP)
                debugOut_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                debugOut_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End debugOut_TXCLKGEN_DP */

            #if( (debugOut_PARITY_TYPE != debugOut__B_UART__NONE_REVB) || \
                 (debugOut_PARITY_TYPE_SW != 0u) )
                debugOut_WriteControlRegister(debugOut_ReadControlRegister() &
                                                      (uint8) ~debugOut_CTRL_HD_SEND_BREAK);
            #endif /* End debugOut_PARITY_TYPE != NONE */
            }
        #endif    /* End debugOut_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: debugOut_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       debugOut_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       debugOut_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears debugOut_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void debugOut_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( debugOut_CONTROL_REG_REMOVED == 0u )
            debugOut_WriteControlRegister(debugOut_ReadControlRegister() |
                                                  debugOut_CTRL_MARK);
        #endif /* End debugOut_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( debugOut_CONTROL_REG_REMOVED == 0u )
            debugOut_WriteControlRegister(debugOut_ReadControlRegister() &
                                                  (uint8) ~debugOut_CTRL_MARK);
        #endif /* End debugOut_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EnddebugOut_TX_ENABLED */

#if(debugOut_HD_ENABLED)


    /*******************************************************************************
    * Function Name: debugOut_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void debugOut_LoadRxConfig(void) 
    {
        debugOut_WriteControlRegister(debugOut_ReadControlRegister() &
                                                (uint8)~debugOut_CTRL_HD_SEND);
        debugOut_RXBITCTR_PERIOD_REG = debugOut_HD_RXBITCTR_INIT;

    #if (debugOut_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        debugOut_SetRxInterruptMode(debugOut_INIT_RX_INTERRUPTS_MASK);
    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: debugOut_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void debugOut_LoadTxConfig(void) 
    {
    #if (debugOut_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        debugOut_SetRxInterruptMode(0u);
    #endif /* (debugOut_RX_INTERRUPT_ENABLED) */

        debugOut_WriteControlRegister(debugOut_ReadControlRegister() | debugOut_CTRL_HD_SEND);
        debugOut_RXBITCTR_PERIOD_REG = debugOut_HD_TXBITCTR_INIT;
    }

#endif  /* debugOut_HD_ENABLED */


/* [] END OF FILE */
