/*******************************************************************************
* File Name: MotRetning.c  
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
#include "MotRetning.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        MotRetning_PC =   (MotRetning_PC & \
                                (uint32)(~(uint32)(MotRetning_DRIVE_MODE_IND_MASK << (MotRetning_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (MotRetning_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: MotRetning_Write
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
void MotRetning_Write(uint8 value) 
{
    uint8 drVal = (uint8)(MotRetning_DR & (uint8)(~MotRetning_MASK));
    drVal = (drVal | ((uint8)(value << MotRetning_SHIFT) & MotRetning_MASK));
    MotRetning_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: MotRetning_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MotRetning_DM_STRONG     Strong Drive 
*  MotRetning_DM_OD_HI      Open Drain, Drives High 
*  MotRetning_DM_OD_LO      Open Drain, Drives Low 
*  MotRetning_DM_RES_UP     Resistive Pull Up 
*  MotRetning_DM_RES_DWN    Resistive Pull Down 
*  MotRetning_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MotRetning_DM_DIG_HIZ    High Impedance Digital 
*  MotRetning_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MotRetning_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(MotRetning__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: MotRetning_Read
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
*  Macro MotRetning_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MotRetning_Read(void) 
{
    return (uint8)((MotRetning_PS & MotRetning_MASK) >> MotRetning_SHIFT);
}


/*******************************************************************************
* Function Name: MotRetning_ReadDataReg
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
uint8 MotRetning_ReadDataReg(void) 
{
    return (uint8)((MotRetning_DR & MotRetning_MASK) >> MotRetning_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MotRetning_INTSTAT) 

    /*******************************************************************************
    * Function Name: MotRetning_ClearInterrupt
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
    uint8 MotRetning_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(MotRetning_INTSTAT & MotRetning_MASK);
		MotRetning_INTSTAT = maskedStatus;
        return maskedStatus >> MotRetning_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
