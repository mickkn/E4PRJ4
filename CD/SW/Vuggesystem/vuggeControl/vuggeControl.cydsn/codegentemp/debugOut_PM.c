/*******************************************************************************
* File Name: debugOut_PM.c
* Version 2.40
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
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
* Local data allocation
***************************************/

static debugOut_BACKUP_STRUCT  debugOut_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: debugOut_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the debugOut_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  debugOut_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void debugOut_SaveConfig(void)
{
    #if(debugOut_CONTROL_REG_REMOVED == 0u)
        debugOut_backup.cr = debugOut_CONTROL_REG;
    #endif /* End debugOut_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: debugOut_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  debugOut_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after debugOut_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void debugOut_RestoreConfig(void)
{
    #if(debugOut_CONTROL_REG_REMOVED == 0u)
        debugOut_CONTROL_REG = debugOut_backup.cr;
    #endif /* End debugOut_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: debugOut_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The debugOut_Sleep() API saves the current component state. Then it
*  calls the debugOut_Stop() function and calls 
*  debugOut_SaveConfig() to save the hardware configuration.
*  Call the debugOut_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  debugOut_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void debugOut_Sleep(void)
{
    #if(debugOut_RX_ENABLED || debugOut_HD_ENABLED)
        if((debugOut_RXSTATUS_ACTL_REG  & debugOut_INT_ENABLE) != 0u)
        {
            debugOut_backup.enableState = 1u;
        }
        else
        {
            debugOut_backup.enableState = 0u;
        }
    #else
        if((debugOut_TXSTATUS_ACTL_REG  & debugOut_INT_ENABLE) !=0u)
        {
            debugOut_backup.enableState = 1u;
        }
        else
        {
            debugOut_backup.enableState = 0u;
        }
    #endif /* End debugOut_RX_ENABLED || debugOut_HD_ENABLED*/

    debugOut_Stop();
    debugOut_SaveConfig();
}


/*******************************************************************************
* Function Name: debugOut_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  debugOut_Sleep() was called. The debugOut_Wakeup() function
*  calls the debugOut_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  debugOut_Sleep() function was called, the debugOut_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  debugOut_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void debugOut_Wakeup(void)
{
    debugOut_RestoreConfig();
    #if( (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) )
        debugOut_ClearRxBuffer();
    #endif /* End (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) */
    #if(debugOut_TX_ENABLED || debugOut_HD_ENABLED)
        debugOut_ClearTxBuffer();
    #endif /* End debugOut_TX_ENABLED || debugOut_HD_ENABLED */

    if(debugOut_backup.enableState != 0u)
    {
        debugOut_Enable();
    }
}


/* [] END OF FILE */
