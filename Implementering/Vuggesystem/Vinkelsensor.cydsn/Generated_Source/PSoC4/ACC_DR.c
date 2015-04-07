/*******************************************************************************
* File Name: ACC_DR.c  
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
#include "ACC_DR.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ACC_DR_PC =   (ACC_DR_PC & \
                                (uint32)(~(uint32)(ACC_DR_DRIVE_MODE_IND_MASK << (ACC_DR_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ACC_DR_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ACC_DR_Write
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
void ACC_DR_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ACC_DR_DR & (uint8)(~ACC_DR_MASK));
    drVal = (drVal | ((uint8)(value << ACC_DR_SHIFT) & ACC_DR_MASK));
    ACC_DR_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ACC_DR_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ACC_DR_DM_STRONG     Strong Drive 
*  ACC_DR_DM_OD_HI      Open Drain, Drives High 
*  ACC_DR_DM_OD_LO      Open Drain, Drives Low 
*  ACC_DR_DM_RES_UP     Resistive Pull Up 
*  ACC_DR_DM_RES_DWN    Resistive Pull Down 
*  ACC_DR_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ACC_DR_DM_DIG_HIZ    High Impedance Digital 
*  ACC_DR_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ACC_DR_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ACC_DR__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ACC_DR_Read
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
*  Macro ACC_DR_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ACC_DR_Read(void) 
{
    return (uint8)((ACC_DR_PS & ACC_DR_MASK) >> ACC_DR_SHIFT);
}


/*******************************************************************************
* Function Name: ACC_DR_ReadDataReg
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
uint8 ACC_DR_ReadDataReg(void) 
{
    return (uint8)((ACC_DR_DR & ACC_DR_MASK) >> ACC_DR_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ACC_DR_INTSTAT) 

    /*******************************************************************************
    * Function Name: ACC_DR_ClearInterrupt
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
    uint8 ACC_DR_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ACC_DR_INTSTAT & ACC_DR_MASK);
		ACC_DR_INTSTAT = maskedStatus;
        return maskedStatus >> ACC_DR_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
