/*******************************************************************************
* File Name: ESSwitch.c  
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
#include "ESSwitch.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ESSwitch_PC =   (ESSwitch_PC & \
                                (uint32)(~(uint32)(ESSwitch_DRIVE_MODE_IND_MASK << (ESSwitch_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ESSwitch_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ESSwitch_Write
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
void ESSwitch_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ESSwitch_DR & (uint8)(~ESSwitch_MASK));
    drVal = (drVal | ((uint8)(value << ESSwitch_SHIFT) & ESSwitch_MASK));
    ESSwitch_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ESSwitch_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ESSwitch_DM_STRONG     Strong Drive 
*  ESSwitch_DM_OD_HI      Open Drain, Drives High 
*  ESSwitch_DM_OD_LO      Open Drain, Drives Low 
*  ESSwitch_DM_RES_UP     Resistive Pull Up 
*  ESSwitch_DM_RES_DWN    Resistive Pull Down 
*  ESSwitch_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ESSwitch_DM_DIG_HIZ    High Impedance Digital 
*  ESSwitch_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ESSwitch_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ESSwitch__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ESSwitch_Read
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
*  Macro ESSwitch_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ESSwitch_Read(void) 
{
    return (uint8)((ESSwitch_PS & ESSwitch_MASK) >> ESSwitch_SHIFT);
}


/*******************************************************************************
* Function Name: ESSwitch_ReadDataReg
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
uint8 ESSwitch_ReadDataReg(void) 
{
    return (uint8)((ESSwitch_DR & ESSwitch_MASK) >> ESSwitch_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ESSwitch_INTSTAT) 

    /*******************************************************************************
    * Function Name: ESSwitch_ClearInterrupt
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
    uint8 ESSwitch_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ESSwitch_INTSTAT & ESSwitch_MASK);
		ESSwitch_INTSTAT = maskedStatus;
        return maskedStatus >> ESSwitch_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
