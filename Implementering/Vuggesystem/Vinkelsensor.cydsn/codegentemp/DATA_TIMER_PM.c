/*******************************************************************************
* File Name: DATA_TIMER_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "DATA_TIMER.h"

static DATA_TIMER_backupStruct DATA_TIMER_backup;


/*******************************************************************************
* Function Name: DATA_TIMER_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DATA_TIMER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DATA_TIMER_SaveConfig(void) 
{
    #if (!DATA_TIMER_UsingFixedFunction)
        DATA_TIMER_backup.TimerUdb = DATA_TIMER_ReadCounter();
        DATA_TIMER_backup.InterruptMaskValue = DATA_TIMER_STATUS_MASK;
        #if (DATA_TIMER_UsingHWCaptureCounter)
            DATA_TIMER_backup.TimerCaptureCounter = DATA_TIMER_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!DATA_TIMER_UDB_CONTROL_REG_REMOVED)
            DATA_TIMER_backup.TimerControlRegister = DATA_TIMER_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: DATA_TIMER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DATA_TIMER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DATA_TIMER_RestoreConfig(void) 
{   
    #if (!DATA_TIMER_UsingFixedFunction)

        DATA_TIMER_WriteCounter(DATA_TIMER_backup.TimerUdb);
        DATA_TIMER_STATUS_MASK =DATA_TIMER_backup.InterruptMaskValue;
        #if (DATA_TIMER_UsingHWCaptureCounter)
            DATA_TIMER_SetCaptureCount(DATA_TIMER_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!DATA_TIMER_UDB_CONTROL_REG_REMOVED)
            DATA_TIMER_WriteControlRegister(DATA_TIMER_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: DATA_TIMER_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DATA_TIMER_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void DATA_TIMER_Sleep(void) 
{
    #if(!DATA_TIMER_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(DATA_TIMER_CTRL_ENABLE == (DATA_TIMER_CONTROL & DATA_TIMER_CTRL_ENABLE))
        {
            /* Timer is enabled */
            DATA_TIMER_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            DATA_TIMER_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    DATA_TIMER_Stop();
    DATA_TIMER_SaveConfig();
}


/*******************************************************************************
* Function Name: DATA_TIMER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DATA_TIMER_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DATA_TIMER_Wakeup(void) 
{
    DATA_TIMER_RestoreConfig();
    #if(!DATA_TIMER_UDB_CONTROL_REG_REMOVED)
        if(DATA_TIMER_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                DATA_TIMER_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
