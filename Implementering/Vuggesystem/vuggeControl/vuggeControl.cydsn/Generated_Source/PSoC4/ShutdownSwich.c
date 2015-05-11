/*******************************************************************************
* File Name: ShutdownSwich.c  
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
#include "ShutdownSwich.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ShutdownSwich_PC =   (ShutdownSwich_PC & \
                                (uint32)(~(uint32)(ShutdownSwich_DRIVE_MODE_IND_MASK << (ShutdownSwich_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ShutdownSwich_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ShutdownSwich_Write
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
void ShutdownSwich_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ShutdownSwich_DR & (uint8)(~ShutdownSwich_MASK));
    drVal = (drVal | ((uint8)(value << ShutdownSwich_SHIFT) & ShutdownSwich_MASK));
    ShutdownSwich_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ShutdownSwich_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ShutdownSwich_DM_STRONG     Strong Drive 
*  ShutdownSwich_DM_OD_HI      Open Drain, Drives High 
*  ShutdownSwich_DM_OD_LO      Open Drain, Drives Low 
*  ShutdownSwich_DM_RES_UP     Resistive Pull Up 
*  ShutdownSwich_DM_RES_DWN    Resistive Pull Down 
*  ShutdownSwich_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ShutdownSwich_DM_DIG_HIZ    High Impedance Digital 
*  ShutdownSwich_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ShutdownSwich_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ShutdownSwich__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ShutdownSwich_Read
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
*  Macro ShutdownSwich_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ShutdownSwich_Read(void) 
{
    return (uint8)((ShutdownSwich_PS & ShutdownSwich_MASK) >> ShutdownSwich_SHIFT);
}


/*******************************************************************************
* Function Name: ShutdownSwich_ReadDataReg
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
uint8 ShutdownSwich_ReadDataReg(void) 
{
    return (uint8)((ShutdownSwich_DR & ShutdownSwich_MASK) >> ShutdownSwich_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ShutdownSwich_INTSTAT) 

    /*******************************************************************************
    * Function Name: ShutdownSwich_ClearInterrupt
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
    uint8 ShutdownSwich_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ShutdownSwich_INTSTAT & ShutdownSwich_MASK);
		ShutdownSwich_INTSTAT = maskedStatus;
        return maskedStatus >> ShutdownSwich_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
