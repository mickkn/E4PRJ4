/*******************************************************************************
* File Name: sensorI2C_I2C_INT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in I2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "sensorI2C_PVT.h"
#include "sensorI2C_I2C_PVT.h"


/*******************************************************************************
* Function Name: sensorI2C_I2C_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB I2C mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(sensorI2C_I2C_ISR)
{
    uint32 diffCount;
    uint32 endTransfer;

    #if(sensorI2C_CHECK_I2C_ACCEPT_ADDRESS_CONST)
        uint32 address;
    #endif /* (sensorI2C_CHECK_I2C_ACCEPT_ADDRESS_CONST) */

    endTransfer = 0u; /* Continue active transfer */

    /* Calls customer routine if registered */
    if(NULL != sensorI2C_customIntrHandler)
    {
        sensorI2C_customIntrHandler();
    }

    if(sensorI2C_CHECK_INTR_I2C_EC_MASKED(sensorI2C_INTR_I2C_EC_WAKE_UP))
    {
        /* Mask-off after wakeup */
        sensorI2C_SetI2CExtClkInterruptMode(sensorI2C_NO_INTR_SOURCES);
    }

    /* Master and Slave error tracking:
    * Add the master state check to track only the master errors when the master is active or
    * track slave errors when the slave is active or idle.
    * A special MMS case: in the address phase with misplaced Start: the master sets the LOST_ARB and
    * slave BUS_ERR. The valid event is LOST_ARB comes from the master.
    */
    if(sensorI2C_CHECK_I2C_FSM_MASTER)
    {
        #if(sensorI2C_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_BUS_ERROR:
            * A misplaced Start or Stop condition occurred on the bus: complete the transaction.
            * The interrupt is cleared in I2C_FSM_EXIT_IDLE.
            */
            if(sensorI2C_CHECK_INTR_MASTER_MASKED(sensorI2C_INTR_MASTER_I2C_BUS_ERROR))
            {
                sensorI2C_mstrStatus |= (uint16) (sensorI2C_I2C_MSTAT_ERR_XFER |
                                                         sensorI2C_I2C_MSTAT_ERR_BUS_ERROR);

                endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
            }

            /* INTR_MASTER_I2C_ARB_LOST:
            * The MultiMaster lost arbitrage during transaction.
            * A Misplaced Start or Stop condition is treated as lost arbitration when the master drives the SDA.
            * The interrupt source is cleared in I2C_FSM_EXIT_IDLE.
            */
            if(sensorI2C_CHECK_INTR_MASTER_MASKED(sensorI2C_INTR_MASTER_I2C_ARB_LOST))
            {
                sensorI2C_mstrStatus |= (uint16) (sensorI2C_I2C_MSTAT_ERR_XFER |
                                                         sensorI2C_I2C_MSTAT_ERR_ARB_LOST);

                endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
            }

            #if(sensorI2C_I2C_MULTI_MASTER_SLAVE)
            {
                /* I2C_MASTER_CMD_M_START_ON_IDLE:
                * MultiMaster-Slave does not generate start, because Slave was addressed.
                * Pass control to slave.
                */
                if(sensorI2C_CHECK_I2C_MASTER_CMD(sensorI2C_I2C_MASTER_CMD_M_START_ON_IDLE))
                {
                    sensorI2C_mstrStatus |= (uint16) (sensorI2C_I2C_MSTAT_ERR_XFER |
                                                             sensorI2C_I2C_MSTAT_ERR_ABORT_XFER);

                    endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                }
            }
            #endif

            /* The error handling common part:
            * Sets a completion flag of the master transaction and passes control to:
            *  - I2C_FSM_EXIT_IDLE - to complete transaction in case of: ARB_LOST or BUS_ERR.
            *  - I2C_FSM_IDLE      - to take chance for the slave to process incoming transaction.
            */
            if(0u != endTransfer)
            {
                /* Set completion flags for master */
                sensorI2C_mstrStatus |= (uint16) sensorI2C_GET_I2C_MSTAT_CMPLT;

                #if(sensorI2C_I2C_MULTI_MASTER_SLAVE)
                {
                    if(sensorI2C_CHECK_I2C_FSM_ADDR)
                    {
                        /* Start generation is set after another master starts accessing Slave.
                        * Clean-up master and turn to slave. Set state to IDLE.
                        */
                        if(sensorI2C_CHECK_I2C_MASTER_CMD(sensorI2C_I2C_MASTER_CMD_M_START_ON_IDLE))
                        {
                            sensorI2C_I2C_MASTER_CLEAR_START;

                            endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        /* Valid arbitration lost on the address phase happens only when: master LOST_ARB is set and
                        * slave BUS_ERR is cleared. Only in that case set the state to IDLE without SCB IP re-enable.
                        */
                        else if((!sensorI2C_CHECK_INTR_SLAVE_MASKED(sensorI2C_INTR_SLAVE_I2C_BUS_ERROR))
                               && sensorI2C_CHECK_INTR_MASTER_MASKED(sensorI2C_INTR_MASTER_I2C_ARB_LOST))
                        {
                            endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        else
                        {
                            endTransfer = 0u; /* Causes I2C_FSM_EXIT_IDLE to be set below */
                        }

                        if(0u != endTransfer) /* Clean-up master to proceed with slave */
                        {
                            sensorI2C_CLEAR_TX_FIFO; /* Shifter keeps address, clear it */

                            sensorI2C_DISABLE_MASTER_AUTO_DATA_ACK; /* In case of reading disable autoACK */

                            /* Clean-up master interrupt sources */
                            sensorI2C_ClearMasterInterruptSource(sensorI2C_INTR_MASTER_ALL);

                            /* Disable data processing interrupts: they have to be cleared before */
                            sensorI2C_SetRxInterruptMode(sensorI2C_NO_INTR_SOURCES);
                            sensorI2C_SetTxInterruptMode(sensorI2C_NO_INTR_SOURCES);

                            sensorI2C_state = sensorI2C_I2C_FSM_IDLE;
                        }
                        else
                        {
                            /* Set I2C_FSM_EXIT_IDLE for BUS_ERR and ARB_LOST (that is really bus error) */
                            sensorI2C_state = sensorI2C_I2C_FSM_EXIT_IDLE;
                        }
                    }
                    else
                    {
                        /* Set I2C_FSM_EXIT_IDLE if any other state than address */
                        sensorI2C_state = sensorI2C_I2C_FSM_EXIT_IDLE;
                    }
                }
                #else
                {
                    /* In case of LOST*/
                    sensorI2C_state = sensorI2C_I2C_FSM_EXIT_IDLE;
                }
                #endif
            }
        }
        #endif
    }
    else /* (sensorI2C_CHECK_I2C_FSM_SLAVE) */
    {
        #if(sensorI2C_I2C_SLAVE)
        {
            /* INTR_SLAVE_I2C_BUS_ERROR or sensorI2C_INTR_SLAVE_I2C_ARB_LOST:
            * A Misplaced Start or Stop condition occurred on the bus: set a flag
            * to notify an error condition.
            */
            if(sensorI2C_CHECK_INTR_SLAVE_MASKED(sensorI2C_INTR_SLAVE_I2C_BUS_ERROR |
                                                        sensorI2C_INTR_SLAVE_I2C_ARB_LOST))
            {
                if(sensorI2C_CHECK_I2C_FSM_RD)
                {
                    /* TX direction: master reads from slave */
                    sensorI2C_slStatus &= (uint8) ~sensorI2C_I2C_SSTAT_RD_BUSY;
                    sensorI2C_slStatus |= (uint8) (sensorI2C_I2C_SSTAT_RD_ERR |
                                                          sensorI2C_I2C_SSTAT_RD_CMPLT);
                }
                else
                {
                    /* RX direction: master writes into slave */
                    sensorI2C_slStatus &= (uint8) ~sensorI2C_I2C_SSTAT_WR_BUSY;
                    sensorI2C_slStatus |= (uint8) (sensorI2C_I2C_SSTAT_WR_ERR |
                                                          sensorI2C_I2C_SSTAT_WR_CMPLT);
                }

                sensorI2C_state = sensorI2C_I2C_FSM_EXIT_IDLE;
            }
        }
        #endif
    }

    /* States description:
    * Any Master operation starts from: the ADDR_RD/WR state as the master generates traffic on the bus.
    * Any Slave operation starts from: the IDLE state as the slave always waits for actions from the master.
    */

    /* FSM Master */
    if(sensorI2C_CHECK_I2C_FSM_MASTER)
    {
        #if(sensorI2C_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_STOP:
            * A Stop condition was generated by the master: the end of the transaction.
            * Set completion flags to notify the API.
            */
            if(sensorI2C_CHECK_INTR_MASTER_MASKED(sensorI2C_INTR_MASTER_I2C_STOP))
            {
                sensorI2C_ClearMasterInterruptSource(sensorI2C_INTR_MASTER_I2C_STOP);

                sensorI2C_mstrStatus |= (uint16) sensorI2C_GET_I2C_MSTAT_CMPLT;
                sensorI2C_state       = sensorI2C_I2C_FSM_IDLE;
            }
            else
            {
                if(sensorI2C_CHECK_I2C_FSM_ADDR) /* Address stage */
                {
                    /* INTR_MASTER_I2C_NACK:
                    * The master sent an address but it was NACKed by the slave. Complete transaction.
                    */
                    if(sensorI2C_CHECK_INTR_MASTER_MASKED(sensorI2C_INTR_MASTER_I2C_NACK))
                    {
                        sensorI2C_ClearMasterInterruptSource(sensorI2C_INTR_MASTER_I2C_NACK);

                        sensorI2C_mstrStatus |= (uint16) (sensorI2C_I2C_MSTAT_ERR_XFER |
                                                                 sensorI2C_I2C_MSTAT_ERR_ADDR_NAK);

                        endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                    }
                    /* INTR_TX_UNDERFLOW. The master sent an address:
                    *  - TX direction: the clock is stretched after the ACK phase, because the TX FIFO is
                    *    EMPTY. The TX EMPTY cleans all the TX interrupt sources.
                    *  - RX direction: the 1st byte is received, but there is no ACK permission,
                    *    the clock is stretched after 1 byte is received.
                    */
                    else
                    {
                        if(sensorI2C_CHECK_I2C_FSM_RD) /* Reading */
                        {
                            sensorI2C_state = sensorI2C_I2C_FSM_MSTR_RD_DATA;
                        }
                        else /* Writing */
                        {
                            sensorI2C_state = sensorI2C_I2C_FSM_MSTR_WR_DATA;
                            if(0u != sensorI2C_mstrWrBufSize)
                            {
                                /* Enable INTR.TX_EMPTY if there is data to transmit */
                                sensorI2C_SetTxInterruptMode(sensorI2C_INTR_TX_EMPTY);
                            }
                        }
                    }
                }

                if(sensorI2C_CHECK_I2C_FSM_DATA) /* Data phase */
                {
                    if(sensorI2C_CHECK_I2C_FSM_RD) /* Reading */
                    {
                        /* INTR_RX_FULL:
                        * RX direction: the master received 8 bytes.
                        * Get data from RX FIFO and decide whether to ACK or  NACK the following bytes.
                        */
                        if(sensorI2C_CHECK_INTR_RX_MASKED(sensorI2C_INTR_RX_FULL))
                        {
                            /* Calculate difference */
                            diffCount =  sensorI2C_mstrRdBufSize -
                                        (sensorI2C_mstrRdBufIndex + sensorI2C_GET_RX_FIFO_ENTRIES);

                            /* Proceed transaction or end it when RX FIFO becomes FULL again */
                            if(diffCount > sensorI2C_I2C_FIFO_SIZE)
                            {
                                diffCount = sensorI2C_I2C_FIFO_SIZE;
                            }
                            else
                            {
                                if(0u == diffCount)
                                {
                                    sensorI2C_DISABLE_MASTER_AUTO_DATA_ACK;

                                    diffCount   = sensorI2C_I2C_FIFO_SIZE;
                                    endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                                }
                            }

                            for(; (0u != diffCount); diffCount--)
                            {
                                sensorI2C_mstrRdBufPtr[sensorI2C_mstrRdBufIndex] = (uint8)
                                                                                        sensorI2C_RX_FIFO_RD_REG;
                                sensorI2C_mstrRdBufIndex++;
                            }
                        }
                        /* INTR_RX_NOT_EMPTY:
                        * RX direction: the master received one data byte, ACK or NACK it.
                        * The last byte is stored and NACKed by the master. The NACK and Stop is
                        * generated by one command generate Stop.
                        */
                        else if(sensorI2C_CHECK_INTR_RX_MASKED(sensorI2C_INTR_RX_NOT_EMPTY))
                        {
                            /* Put data in component buffer */
                            sensorI2C_mstrRdBufPtr[sensorI2C_mstrRdBufIndex] = (uint8) sensorI2C_RX_FIFO_RD_REG;
                            sensorI2C_mstrRdBufIndex++;

                            if(sensorI2C_mstrRdBufIndex < sensorI2C_mstrRdBufSize)
                            {
                                sensorI2C_I2C_MASTER_GENERATE_ACK;
                            }
                            else
                            {
                               endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                            }
                        }
                        else
                        {
                            /* Do nothing */
                        }

                        sensorI2C_ClearRxInterruptSource(sensorI2C_INTR_RX_ALL);
                    }
                    else /* Writing */
                    {
                        /* INTR_MASTER_I2C_NACK :
                        * The master writes data to the slave and NACK was received: not all the bytes were
                        * written to the slave from the TX FIFO. Revert the index if there is data in
                        * the TX FIFO and pass control to a complete transfer.
                        */
                        if(sensorI2C_CHECK_INTR_MASTER_MASKED(sensorI2C_INTR_MASTER_I2C_NACK))
                        {
                            sensorI2C_ClearMasterInterruptSource(sensorI2C_INTR_MASTER_I2C_NACK);

                            /* Rollback write buffer index: NACKed byte remains in shifter */
                            sensorI2C_mstrWrBufIndexTmp -= (sensorI2C_GET_TX_FIFO_ENTRIES +
                                                                   sensorI2C_GET_TX_FIFO_SR_VALID);

                            /* Update number of transferred bytes */
                            sensorI2C_mstrWrBufIndex = sensorI2C_mstrWrBufIndexTmp;

                            sensorI2C_mstrStatus |= (uint16) (sensorI2C_I2C_MSTAT_ERR_XFER |
                                                                     sensorI2C_I2C_MSTAT_ERR_SHORT_XFER);

                            sensorI2C_CLEAR_TX_FIFO;

                            endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                        }
                        /* INTR_TX_EMPTY :
                        * TX direction: the TX FIFO is EMPTY, the data from the buffer needs to be put there.
                        * When there is no data in the component buffer, the underflow interrupt is
                        * enabled to catch when all the data has been transferred.
                        */
                        else if(sensorI2C_CHECK_INTR_TX_MASKED(sensorI2C_INTR_TX_EMPTY))
                        {
                            while(sensorI2C_I2C_FIFO_SIZE != sensorI2C_GET_TX_FIFO_ENTRIES)
                            {
                                /* The temporary mstrWrBufIndexTmp is used because slave could NACK the byte and index
                                * roll-back required in this case. The mstrWrBufIndex is updated at the end of transfer.
                                */
                                if(sensorI2C_mstrWrBufIndexTmp < sensorI2C_mstrWrBufSize)
                                {
                                #if(!sensorI2C_CY_SCBIP_V0)
                                   /* Clear INTR_TX.UNDERFLOW before putting the last byte into TX FIFO. This ensures
                                    * a proper trigger at the end of transaction when INTR_TX.UNDERFLOW single trigger
                                    * event. Ticket ID# 156735.
                                    */
                                    if(sensorI2C_mstrWrBufIndexTmp == (sensorI2C_mstrWrBufSize - 1u))
                                    {
                                        sensorI2C_ClearTxInterruptSource(sensorI2C_INTR_TX_UNDERFLOW);
                                        sensorI2C_SetTxInterruptMode(sensorI2C_INTR_TX_UNDERFLOW);
                                    }
                                 #endif /* (!sensorI2C_CY_SCBIP_V0) */

                                    /* Put data into TX FIFO */
                                    sensorI2C_TX_FIFO_WR_REG = (uint32) sensorI2C_mstrWrBufPtr[sensorI2C_mstrWrBufIndexTmp];
                                    sensorI2C_mstrWrBufIndexTmp++;
                                }
                                else
                                {
                                    break; /* No more data to put */
                                }
                            }

                        #if(sensorI2C_CY_SCBIP_V0)
                            if(sensorI2C_mstrWrBufIndexTmp == sensorI2C_mstrWrBufSize)
                            {
                                sensorI2C_SetTxInterruptMode(sensorI2C_INTR_TX_UNDERFLOW);
                            }

                            sensorI2C_ClearTxInterruptSource(sensorI2C_INTR_TX_ALL);
                        #else
                            sensorI2C_ClearTxInterruptSource(sensorI2C_INTR_TX_EMPTY);
                        #endif /* (sensorI2C_CY_SCBIP_V0) */
                        }
                        /* INTR_TX_UNDERFLOW:
                        * TX direction: all data from the TX FIFO was transferred to the slave.
                        * The transaction needs to be completed.
                        */
                        else if(sensorI2C_CHECK_INTR_TX_MASKED(sensorI2C_INTR_TX_UNDERFLOW))
                        {
                            /* Update number of transferred bytes */
                            sensorI2C_mstrWrBufIndex = sensorI2C_mstrWrBufIndexTmp;

                            endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                }

                if(0u != endTransfer) /* Complete transfer */
                {
                    /* Clean-up master after reading: only in case of NACK */
                    sensorI2C_DISABLE_MASTER_AUTO_DATA_ACK;

                    /* Disable data processing interrupts: they have to be cleared before */
                    sensorI2C_SetRxInterruptMode(sensorI2C_NO_INTR_SOURCES);
                    sensorI2C_SetTxInterruptMode(sensorI2C_NO_INTR_SOURCES);

                    if(sensorI2C_CHECK_I2C_MODE_NO_STOP(sensorI2C_mstrControl))
                    {
                        /* On-going transaction is suspended: the ReStart is generated by the API request */
                        sensorI2C_mstrStatus |= (uint16) (sensorI2C_I2C_MSTAT_XFER_HALT |
                                                                 sensorI2C_GET_I2C_MSTAT_CMPLT);

                        sensorI2C_state = sensorI2C_I2C_FSM_MSTR_HALT;
                    }
                    else
                    {
                        /* Complete transaction: exclude the data processing state and generate Stop.
                        * The completion status will be set after Stop generation.
                        * A special case is read: because NACK and Stop are generated by the command below.
                        * Lost arbitration can occur during NACK generation when
                        * the other master is still reading from the slave.
                        */
                        sensorI2C_I2C_MASTER_GENERATE_STOP;
                    }
                }
            }

        } /* (sensorI2C_I2C_MASTER) */
        #endif

    } /* (sensorI2C_CHECK_I2C_FSM_MASTER) */


    /* FSM Slave */
    else if(sensorI2C_CHECK_I2C_FSM_SLAVE)
    {
        #if(sensorI2C_I2C_SLAVE)
        {
            /* INTR_SLAVE_NACK:
            * The master completes reading the slave: the appropriate flags have to be set.
            * The TX FIFO is cleared after an overflow condition is set.
            */
            if(sensorI2C_CHECK_INTR_SLAVE_MASKED(sensorI2C_INTR_SLAVE_I2C_NACK))
            {
                sensorI2C_ClearSlaveInterruptSource(sensorI2C_INTR_SLAVE_I2C_NACK);

                /* All entries that remain in TX FIFO max value is 9: 8 (FIFO) + 1 (SHIFTER) */
                diffCount = (sensorI2C_GET_TX_FIFO_ENTRIES + sensorI2C_GET_TX_FIFO_SR_VALID);

                if(sensorI2C_slOverFlowCount > diffCount) /* Overflow */
                {
                    sensorI2C_slStatus |= (uint8) sensorI2C_I2C_SSTAT_RD_OVFL;
                }
                else /* No Overflow */
                {
                    /* Roll-back temporary index */
                    sensorI2C_slRdBufIndexTmp -= (diffCount - sensorI2C_slOverFlowCount);
                }

                /* Update slave of transferred bytes */
                sensorI2C_slRdBufIndex = sensorI2C_slRdBufIndexTmp;

                /* Clean-up TX FIFO */
                sensorI2C_SetTxInterruptMode(sensorI2C_NO_INTR_SOURCES);
                sensorI2C_slOverFlowCount = 0u;
                sensorI2C_CLEAR_TX_FIFO;

                /* Complete master reading */
                sensorI2C_slStatus &= (uint8) ~sensorI2C_I2C_SSTAT_RD_BUSY;
                sensorI2C_slStatus |= (uint8)  sensorI2C_I2C_SSTAT_RD_CMPLT;
                sensorI2C_state     =  sensorI2C_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_WRITE_STOP:
            * The master completes writing to the slave: the appropriate flags have to be set.
            * The RX FIFO contains 1-8 bytes from the previous transaction which needs to be read.
            * There is a possibility that RX FIFO contains an address, it needs to leave it there.
            */
            if(sensorI2C_CHECK_INTR_SLAVE_MASKED(sensorI2C_INTR_SLAVE_I2C_WRITE_STOP))
            {
                sensorI2C_ClearSlaveInterruptSource(sensorI2C_INTR_SLAVE_I2C_WRITE_STOP);

                /* Read bytes from RX FIFO when auto data ACK receive logic is enabled. Otherwise all data bytes
                * were already read from the RX FIFO except for address byte which has to stay here to be handled by
                * I2C_ADDR_MATCH.
                */
                if (0u != (sensorI2C_I2C_CTRL_REG & sensorI2C_I2C_CTRL_S_READY_DATA_ACK))
                {
                    while(0u != sensorI2C_GET_RX_FIFO_ENTRIES)
                    {
                        #if(sensorI2C_CHECK_I2C_ACCEPT_ADDRESS)
                        {
                            if((1u == sensorI2C_GET_RX_FIFO_ENTRIES) &&
                               (sensorI2C_CHECK_INTR_SLAVE_MASKED(sensorI2C_INTR_SLAVE_I2C_ADDR_MATCH)))
                            {
                                break; /* Leave address in RX FIFO */
                            }
                        }
                        #endif

                        /* Put data in component buffer */
                        sensorI2C_slWrBufPtr[sensorI2C_slWrBufIndex] = (uint8) sensorI2C_RX_FIFO_RD_REG;
                        sensorI2C_slWrBufIndex++;
                    }

                    sensorI2C_DISABLE_SLAVE_AUTO_DATA;
                }

                if(sensorI2C_CHECK_INTR_RX(sensorI2C_INTR_RX_OVERFLOW))
                {
                    sensorI2C_slStatus |= (uint8) sensorI2C_I2C_SSTAT_WR_OVFL;
                }

                /* Clears RX interrupt sources triggered on data receiving */
                sensorI2C_SetRxInterruptMode(sensorI2C_NO_INTR_SOURCES);
                sensorI2C_ClearRxInterruptSource(sensorI2C_INTR_RX_ALL);

                /* Complete master writing */
                sensorI2C_slStatus &= (uint8) ~sensorI2C_I2C_SSTAT_WR_BUSY;
                sensorI2C_slStatus |= (uint8)  sensorI2C_I2C_SSTAT_WR_CMPLT;
                sensorI2C_state     =  sensorI2C_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_ADDR_MATCH:
            * The address match event starts the slave operation: after leaving the TX or RX
            * direction has to be chosen.
            * The wakeup interrupt must be cleared only after an address match is set.
            */
            if(sensorI2C_CHECK_INTR_SLAVE_MASKED(sensorI2C_INTR_SLAVE_I2C_ADDR_MATCH))
            {
                #if(sensorI2C_CHECK_I2C_ACCEPT_ADDRESS)
                {
                    address = sensorI2C_RX_FIFO_RD_REG; /* Address in the RX FIFO */

                    /* Clears RX sources if address was received in RX FIFO */
                    sensorI2C_ClearRxInterruptSource(sensorI2C_INTR_RX_ALL);

                    if(0u != address)
                    {
                        /* Suppress compiler warning */
                    }
                }
                #endif

                if(sensorI2C_CHECK_I2C_STATUS(sensorI2C_I2C_STATUS_S_READ))
                /* TX direction: master reads from slave */
                {
                    sensorI2C_SetTxInterruptMode(sensorI2C_INTR_TX_EMPTY);

                    /* Set temporary index to address buffer clear from API */
                    sensorI2C_slRdBufIndexTmp = sensorI2C_slRdBufIndex;

                    /* Start master reading */
                    sensorI2C_slStatus |= (uint8) sensorI2C_I2C_SSTAT_RD_BUSY;
                    sensorI2C_state     = sensorI2C_I2C_FSM_SL_RD;
                }
                else
                /* RX direction: master writes into slave */
                {
                    /* Calculate available buffer size */
                    diffCount = (sensorI2C_slWrBufSize - sensorI2C_slWrBufIndex);

                #if (sensorI2C_CY_SCBIP_V0)

                    if(diffCount < sensorI2C_I2C_FIFO_SIZE)
                    /* Receive data: byte-by-byte */
                    {
                        sensorI2C_SetRxInterruptMode(sensorI2C_INTR_RX_NOT_EMPTY);
                    }
                    else
                    /* Receive data: into RX FIFO */
                    {
                        if(diffCount == sensorI2C_I2C_FIFO_SIZE)
                        {
                            /* NACK when RX FIFO become FULL */
                            sensorI2C_ENABLE_SLAVE_AUTO_DATA;
                        }
                        else
                        {
                            /* Stretch clock when RX FIFO becomes FULL */
                            sensorI2C_ENABLE_SLAVE_AUTO_DATA_ACK;
                            sensorI2C_SetRxInterruptMode(sensorI2C_INTR_RX_FULL);
                        }
                    }

                #else

                    #if(sensorI2C_CHECK_I2C_ACCEPT_ADDRESS)
                    {
                        /* Enable RX.NOT_EMPTY interrupt source to receive byte by byte.
                        * The byte by byte receive is always chosen for the case when an address is accepted in RX FIFO.
                        * Ticket ID#175559.
                        */
                        sensorI2C_SetRxInterruptMode(sensorI2C_INTR_RX_NOT_EMPTY);
                    }
                    #else
                    {
                        if(diffCount < sensorI2C_I2C_FIFO_SIZE)
                        /* Receive data: byte-by-byte */
                        {
                            sensorI2C_SetRxInterruptMode(sensorI2C_INTR_RX_NOT_EMPTY);
                        }
                        else
                        /* Receive data: into RX FIFO */
                        {
                            if(diffCount == sensorI2C_I2C_FIFO_SIZE)
                            {
                                /* NACK when RX FIFO become FULL */
                                sensorI2C_ENABLE_SLAVE_AUTO_DATA;
                            }
                            else
                            {
                                /* Stretch clock when RX FIFO becomes FULL */
                                sensorI2C_ENABLE_SLAVE_AUTO_DATA_ACK;
                                sensorI2C_SetRxInterruptMode(sensorI2C_INTR_RX_FULL);
                            }
                        }
                    }
                    #endif

                #endif /* (sensorI2C_CY_SCBIP_V0) */

                    /* Start master reading */
                    sensorI2C_slStatus |= (uint8) sensorI2C_I2C_SSTAT_WR_BUSY;
                    sensorI2C_state     = sensorI2C_I2C_FSM_SL_WR;
                }

                /* Clear interrupts before ACK address */
                sensorI2C_ClearI2CExtClkInterruptSource(sensorI2C_INTR_I2C_EC_WAKE_UP);
                sensorI2C_ClearSlaveInterruptSource(sensorI2C_INTR_SLAVE_ALL);

                /* Preparation complete: ACK the address */
                sensorI2C_I2C_SLAVE_GENERATE_ACK;
            }

            /* sensorI2C_INTR_RX_FULL:
            * Get data from the RX FIFO and decide whether to ACK or NACK the following bytes
            */
            if(sensorI2C_CHECK_INTR_RX_MASKED(sensorI2C_INTR_RX_FULL))
            {
                /* Calculate available buffer size to take into account that RX FIFO is FULL */
                diffCount =  sensorI2C_slWrBufSize -
                            (sensorI2C_slWrBufIndex + sensorI2C_I2C_FIFO_SIZE);

                if(diffCount > sensorI2C_I2C_FIFO_SIZE) /* Proceed transaction */
                {
                    diffCount   = sensorI2C_I2C_FIFO_SIZE;
                    endTransfer = 0u;  /* Continue active transfer */
                }
                else /* End when FIFO becomes FULL again */
                {
                    endTransfer = sensorI2C_I2C_CMPLT_ANY_TRANSFER;
                }

                for(; (0u != diffCount); diffCount--)
                {
                    /* Put data in component buffer */
                    sensorI2C_slWrBufPtr[sensorI2C_slWrBufIndex] = (uint8) sensorI2C_RX_FIFO_RD_REG;
                    sensorI2C_slWrBufIndex++;
                }

                if(0u != endTransfer) /* End transfer sending NACK */
                {
                    sensorI2C_ENABLE_SLAVE_AUTO_DATA_NACK;

                    /* INTR_RX_FULL triggers earlier than INTR_SLAVE_I2C_STOP:
                    * disable all RX interrupt sources.
                    */
                    sensorI2C_SetRxInterruptMode(sensorI2C_NO_INTR_SOURCES);
                }

                sensorI2C_ClearRxInterruptSource(sensorI2C_INTR_RX_FULL);
            }
            /* sensorI2C_INTR_RX_NOT_EMPTY:
            * The buffer size is less than 8: it requires processing in byte-by-byte mode.
            */
            else if(sensorI2C_CHECK_INTR_RX_MASKED(sensorI2C_INTR_RX_NOT_EMPTY))
            {
                diffCount = sensorI2C_RX_FIFO_RD_REG;

                if(sensorI2C_slWrBufIndex < sensorI2C_slWrBufSize)
                {
                    sensorI2C_I2C_SLAVE_GENERATE_ACK;

                    /* Put data into component buffer */
                    sensorI2C_slWrBufPtr[sensorI2C_slWrBufIndex] = (uint8) diffCount;
                    sensorI2C_slWrBufIndex++;
                }
                else /* Overflow: there is no space in write buffer */
                {
                    sensorI2C_I2C_SLAVE_GENERATE_NACK;

                    sensorI2C_slStatus |= (uint8) sensorI2C_I2C_SSTAT_WR_OVFL;
                }

                sensorI2C_ClearRxInterruptSource(sensorI2C_INTR_RX_NOT_EMPTY);
            }
            else
            {
                /* Does nothing */
            }


            /* sensorI2C_INTR_TX_EMPTY:
            * The master reads the slave: provide data to read or 0xFF in the case of the end of the buffer
            * The overflow condition must be captured, but not set until the end of transaction.
            * There is a possibility of a false overflow due to TX FIFO utilization.
            */
            if(sensorI2C_CHECK_INTR_TX_MASKED(sensorI2C_INTR_TX_EMPTY))
            {
                while(sensorI2C_I2C_FIFO_SIZE != sensorI2C_GET_TX_FIFO_ENTRIES)
                {
                    /* Temporary slRdBufIndexTmp is used because the master can NACK the byte and
                    * index roll-back is required in this case. The slRdBufIndex is updated at the end
                    * of the read transfer.
                    */
                    if(sensorI2C_slRdBufIndexTmp < sensorI2C_slRdBufSize)
                    /* Data from buffer */
                    {
                        sensorI2C_TX_FIFO_WR_REG = (uint32) sensorI2C_slRdBufPtr[sensorI2C_slRdBufIndexTmp];
                        sensorI2C_slRdBufIndexTmp++;
                    }
                    else
                    /* Probably Overflow */
                    {
                        sensorI2C_TX_FIFO_WR_REG = sensorI2C_I2C_SLAVE_OVFL_RETURN;

                        if(0u == (sensorI2C_INTR_TX_OVERFLOW & sensorI2C_slOverFlowCount))
                        {
                            /* Get counter in range of byte: value 10 is overflow */
                            sensorI2C_slOverFlowCount++;
                        }
                    }
                }

                sensorI2C_ClearTxInterruptSource(sensorI2C_INTR_TX_EMPTY);
            }

        }  /* (sensorI2C_I2C_SLAVE) */
        #endif
    }


    /* FSM EXIT:
    * Slave:  INTR_SLAVE_I2C_BUS_ERROR, INTR_SLAVE_I2C_ARB_LOST
    * Master: INTR_MASTER_I2C_BUS_ERROR, INTR_MASTER_I2C_ARB_LOST.
    */
    else
    {
        sensorI2C_CTRL_REG &= (uint32) ~sensorI2C_CTRL_ENABLED; /* Disable scb IP */

        sensorI2C_state = sensorI2C_I2C_FSM_IDLE;

        sensorI2C_DISABLE_SLAVE_AUTO_DATA;
        sensorI2C_DISABLE_MASTER_AUTO_DATA;

    #if(sensorI2C_CY_SCBIP_V0)
        sensorI2C_SetRxInterruptMode(sensorI2C_NO_INTR_SOURCES);
        sensorI2C_SetTxInterruptMode(sensorI2C_NO_INTR_SOURCES);

        /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
        sensorI2C_ClearTxInterruptSource(sensorI2C_INTR_RX_ALL);
        sensorI2C_ClearRxInterruptSource(sensorI2C_INTR_TX_ALL);
        sensorI2C_ClearSlaveInterruptSource(sensorI2C_INTR_SLAVE_ALL);
        sensorI2C_ClearMasterInterruptSource(sensorI2C_INTR_MASTER_ALL);
    #endif /* (sensorI2C_CY_SCBIP_V0) */

        sensorI2C_CTRL_REG |= (uint32) sensorI2C_CTRL_ENABLED;  /* Enable scb IP */
    }
}


/* [] END OF FILE */
