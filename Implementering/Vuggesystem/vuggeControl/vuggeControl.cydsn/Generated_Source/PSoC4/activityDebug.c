/*******************************************************************************
* File Name: activityDebug.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "activityDebug.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        activityDebug_PC =   (activityDebug_PC & \
                                (uint32)(~(uint32)(activityDebug_DRIVE_MODE_IND_MASK << (activityDebug_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (activityDebug_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: activityDebug_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void activityDebug_Write(uint8 value) 
{
    uint8 drVal = (uint8)(activityDebug_DR & (uint8)(~activityDebug_MASK));
    drVal = (drVal | ((uint8)(value << activityDebug_SHIFT) & activityDebug_MASK));
    activityDebug_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: activityDebug_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  activityDebug_DM_STRONG     Strong Drive 
*  activityDebug_DM_OD_HI      Open Drain, Drives High 
*  activityDebug_DM_OD_LO      Open Drain, Drives Low 
*  activityDebug_DM_RES_UP     Resistive Pull Up 
*  activityDebug_DM_RES_DWN    Resistive Pull Down 
*  activityDebug_DM_RES_UPDWN  Resistive Pull Up/Down 
*  activityDebug_DM_DIG_HIZ    High Impedance Digital 
*  activityDebug_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void activityDebug_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(activityDebug__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: activityDebug_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro activityDebug_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 activityDebug_Read(void) 
{
    return (uint8)((activityDebug_PS & activityDebug_MASK) >> activityDebug_SHIFT);
}


/*******************************************************************************
* Function Name: activityDebug_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 activityDebug_ReadDataReg(void) 
{
    return (uint8)((activityDebug_DR & activityDebug_MASK) >> activityDebug_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(activityDebug_INTSTAT) 

    /*******************************************************************************
    * Function Name: activityDebug_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 activityDebug_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(activityDebug_INTSTAT & activityDebug_MASK);
		activityDebug_INTSTAT = maskedStatus;
        return maskedStatus >> activityDebug_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
