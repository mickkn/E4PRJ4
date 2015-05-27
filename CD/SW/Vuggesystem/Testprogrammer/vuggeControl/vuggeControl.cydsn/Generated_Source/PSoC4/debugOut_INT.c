/*******************************************************************************
* File Name: debugOutINT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
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


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (debugOut_RX_INTERRUPT_ENABLED && (debugOut_RX_ENABLED || debugOut_HD_ENABLED))
    /*******************************************************************************
    * Function Name: debugOut_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_rxBuffer - RAM buffer pointer for save received data.
    *  debugOut_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  debugOut_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  debugOut_rxBufferOverflow - software overflow flag. Set to one
    *     when debugOut_rxBufferWrite index overtakes
    *     debugOut_rxBufferRead index.
    *  debugOut_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when debugOut_rxBufferWrite is equal to
    *    debugOut_rxBufferRead
    *  debugOut_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  debugOut_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(debugOut_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START debugOut_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData = debugOut_RXSTATUS_REG;

        if((readData & (debugOut_RX_STS_BREAK | debugOut_RX_STS_PAR_ERROR |
                        debugOut_RX_STS_STOP_ERROR | debugOut_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            debugOut_errorStatus = readData & ( debugOut_RX_STS_BREAK | 
                                                        debugOut_RX_STS_PAR_ERROR | 
                                                        debugOut_RX_STS_STOP_ERROR | 
                                                        debugOut_RX_STS_OVERRUN);
            /* `#START debugOut_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & debugOut_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (debugOut_RXHW_ADDRESS_ENABLED)
            if(debugOut_rxAddressMode == (uint8)debugOut__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & debugOut_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & debugOut_RX_STS_ADDR_MATCH) != 0u)
                    {
                        debugOut_rxAddressDetected = 1u;
                    }
                    else
                    {
                        debugOut_rxAddressDetected = 0u;
                    }
                }

                readData = debugOut_RXDATA_REG;
                if(debugOut_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    debugOut_rxBuffer[debugOut_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            }
            else /* Without software addressing */
            {
                debugOut_rxBuffer[debugOut_rxBufferWrite] = debugOut_RXDATA_REG;
                increment_pointer = 1u;
            }
        #else  /* Without addressing */
            debugOut_rxBuffer[debugOut_rxBufferWrite] = debugOut_RXDATA_REG;
            increment_pointer = 1u;
        #endif /* (debugOut_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(debugOut_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    debugOut_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                debugOut_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(debugOut_rxBufferWrite >= debugOut_RX_BUFFER_SIZE)
                {
                    debugOut_rxBufferWrite = 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(debugOut_rxBufferWrite == debugOut_rxBufferRead)
                {
                    debugOut_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if (debugOut_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        debugOut_RXSTATUS_MASK_REG  &= (uint8)~debugOut_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(debugOut_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (debugOut_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData = debugOut_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START debugOut_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (debugOut_RX_INTERRUPT_ENABLED && (debugOut_RX_ENABLED || debugOut_HD_ENABLED)) */


#if (debugOut_TX_INTERRUPT_ENABLED && debugOut_TX_ENABLED)
    /*******************************************************************************
    * Function Name: debugOut_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  debugOut_txBuffer - RAM buffer pointer for transmit data from.
    *  debugOut_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  debugOut_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(debugOut_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START debugOut_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((debugOut_txBufferRead != debugOut_txBufferWrite) &&
             ((debugOut_TXSTATUS_REG & debugOut_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(debugOut_txBufferRead >= debugOut_TX_BUFFER_SIZE)
            {
                debugOut_txBufferRead = 0u;
            }

            debugOut_TXDATA_REG = debugOut_txBuffer[debugOut_txBufferRead];

            /* Set next pointer */
            debugOut_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START debugOut_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (debugOut_TX_INTERRUPT_ENABLED && debugOut_TX_ENABLED) */


/* [] END OF FILE */
