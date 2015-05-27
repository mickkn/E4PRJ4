/*******************************************************************************
* File Name: I2CVuggesystem_I2C_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component I2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CVuggesystem_BOOT.h"
#include "I2CVuggesystem_I2C_PVT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED)

/***************************************
*    Private I/O Component Vars
***************************************/

/* Writes to this buffer */
static uint8 I2CVuggesystem_slReadBuf[I2CVuggesystem_I2C_BTLDR_SIZEOF_READ_BUFFER];

/* Reads from this buffer */
static uint8 I2CVuggesystem_slWriteBuf[I2CVuggesystem_I2C_BTLDR_SIZEOF_WRITE_BUFFER];

/* Flag to release buffer to be read */
static uint32 I2CVuggesystem_applyBuffer;


/***************************************
*    Private Function Prototypes
***************************************/

static void I2CVuggesystem_I2CResposeInsert(void);


/*******************************************************************************
* Function Name: I2CVuggesystem_I2CCyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the I2C component and enables its interrupt.
*  Every incoming I2C write transaction is treated as a command for the
*  bootloader.
*  Every incoming I2C read transaction returns 0xFF until the bootloader
*  provides a response to the executed command.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CVuggesystem_I2CCyBtldrCommStart(void)
{
    I2CVuggesystem_I2CSlaveInitWriteBuf(I2CVuggesystem_slWriteBuf, I2CVuggesystem_I2C_BTLDR_SIZEOF_WRITE_BUFFER);
    I2CVuggesystem_I2CSlaveInitReadBuf (I2CVuggesystem_slReadBuf, 0u);

    I2CVuggesystem_SetCustomInterruptHandler(&I2CVuggesystem_I2CResposeInsert);
    I2CVuggesystem_applyBuffer = 0u;

    I2CVuggesystem_Start();
}


/*******************************************************************************
* Function Name: I2CVuggesystem_I2CCyBtldrCommStop
********************************************************************************
*
* Summary:
*  Disables the I2C component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CVuggesystem_I2CCyBtldrCommStop(void)
{
    I2CVuggesystem_Stop();
}


/*******************************************************************************
* Function Name: I2CVuggesystem_I2CCyBtldrCommReset
********************************************************************************
*
* Summary:
*  Sets read and write I2C buffers to the initial state and resets the slave
*  status.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*
*
*******************************************************************************/
void I2CVuggesystem_I2CCyBtldrCommReset(void)
{
    /* Make the read buffer full */
    I2CVuggesystem_slRdBufSize = 0u;

    /* Reset write buffer and Read buffer */
    I2CVuggesystem_slRdBufIndex = 0u;
    I2CVuggesystem_slWrBufIndex = 0u;

    /* Clear read and write status */
    I2CVuggesystem_slStatus = 0u;
}


/*******************************************************************************
* Function Name: I2CVuggesystem_I2CCyBtldrCommRead
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the bootloader host.
*  The function handles polling to allow a block of data to be completely
*  received from the host device.
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
* Global variables:
*  I2CVuggesystem_slWriteBuf - used to store received command.
*
*******************************************************************************/
cystatus I2CVuggesystem_I2CCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 timeoutMs;

    status = CYRET_BAD_PARAM;

    if((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        while(0u != timeoutMs)
        {
            /* Check if host complete write */
            if(0u != (I2CVuggesystem_I2C_SSTAT_WR_CMPLT & I2CVuggesystem_slStatus))
            {
                /* Copy command into bootloader buffer */
                (void) memcpy((void *) pData, (const void *) I2CVuggesystem_slWriteBuf,
                                                I2CVuggesystem_I2C_MIN_UINT16(I2CVuggesystem_slWrBufIndex, size));

                /* Copy number of written bytes */
                *count = (uint16) I2CVuggesystem_slWrBufIndex;

                /* Clear write buffer and status */
                I2CVuggesystem_slStatus     = 0u;
                I2CVuggesystem_slWrBufIndex = 0u;

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(I2CVuggesystem_WAIT_1_MS);
            timeoutMs--;
        }
    }

    return(status);
}


/*******************************************************************************
* Function Name: I2CVuggesystem_I2CCyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the bootloader host.
*  The function handles polling to allow a block of data to be completely sent
*  to the host device.
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
* Global variables:
*  I2CVuggesystem_slReadBuf - used to store response.
*  I2CVuggesystem_slRdBufIndex - used to store current index within slave
*  read buffer.
*
*******************************************************************************/
cystatus I2CVuggesystem_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 timeoutMs;

    status = CYRET_BAD_PARAM;

    if((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS checks to 1mS checks */

        /* Copy response into read buffer */
        (void) memcpy((void *) I2CVuggesystem_slReadBuf, (const void *) pData, (uint32) size);
        *count = size; /* Buffer was copied to I2C buffer */

        /* Read buffer is ready to be released to host */
        I2CVuggesystem_applyBuffer = (uint32) size;

        while(0u != timeoutMs)
        {
            /* Check if response has been read */
            if(I2CVuggesystem_slRdBufIndex == (uint32) size)
            {
                /* Invalidate read buffer */
                I2CVuggesystem_slRdBufSize  = 0u;
                I2CVuggesystem_slRdBufIndex = 0u;

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(I2CVuggesystem_WAIT_1_MS);
            timeoutMs--;
        }
    }

    return(status);
}


/*******************************************************************************
* Function Name: I2CVuggesystem_I2CResposeInsert
********************************************************************************
*
* Summary:
*  Releases the read buffer to be read when a response is copied to the buffer
*  and a new read transaction starts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  I2CVuggesystem_slRdBufIndex - used to store current index within slave
*  read buffer.
*  I2CVuggesystem_applyBuffer - flag to release buffer with response to be
*  read
*
*******************************************************************************/
static void I2CVuggesystem_I2CResposeInsert(void)
{
    if(I2CVuggesystem_CHECK_INTR_SLAVE_MASKED(I2CVuggesystem_INTR_SLAVE_I2C_ADDR_MATCH))
    {
        if(0u != I2CVuggesystem_applyBuffer)
        {
            /* Response was copied into buffer: release buffer to host */
            I2CVuggesystem_slRdBufSize = I2CVuggesystem_applyBuffer;
            I2CVuggesystem_applyBuffer = 0u;
        }
    }
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CVuggesystem_I2C_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
