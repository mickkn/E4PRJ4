/*******************************************************************************
* File Name: loopTimer_PM.c
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

#include "loopTimer.h"

static loopTimer_backupStruct loopTimer_backup;


/*******************************************************************************
* Function Name: loopTimer_SaveConfig
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
*  loopTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void loopTimer_SaveConfig(void) 
{
    #if (!loopTimer_UsingFixedFunction)
        loopTimer_backup.TimerUdb = loopTimer_ReadCounter();
        loopTimer_backup.InterruptMaskValue = loopTimer_STATUS_MASK;
        #if (loopTimer_UsingHWCaptureCounter)
            loopTimer_backup.TimerCaptureCounter = loopTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!loopTimer_UDB_CONTROL_REG_REMOVED)
            loopTimer_backup.TimerControlRegister = loopTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: loopTimer_RestoreConfig
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
*  loopTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void loopTimer_RestoreConfig(void) 
{   
    #if (!loopTimer_UsingFixedFunction)

        loopTimer_WriteCounter(loopTimer_backup.TimerUdb);
        loopTimer_STATUS_MASK =loopTimer_backup.InterruptMaskValue;
        #if (loopTimer_UsingHWCaptureCounter)
            loopTimer_SetCaptureCount(loopTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!loopTimer_UDB_CONTROL_REG_REMOVED)
            loopTimer_WriteControlRegister(loopTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: loopTimer_Sleep
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
*  loopTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void loopTimer_Sleep(void) 
{
    #if(!loopTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(loopTimer_CTRL_ENABLE == (loopTimer_CONTROL & loopTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            loopTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            loopTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    loopTimer_Stop();
    loopTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: loopTimer_Wakeup
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
*  loopTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void loopTimer_Wakeup(void) 
{
    loopTimer_RestoreConfig();
    #if(!loopTimer_UDB_CONTROL_REG_REMOVED)
        if(loopTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                loopTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
