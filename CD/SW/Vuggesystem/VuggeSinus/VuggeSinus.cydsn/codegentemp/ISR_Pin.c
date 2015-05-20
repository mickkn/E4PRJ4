/*******************************************************************************
* File Name: ISR_Pin.c  
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
#include "ISR_Pin.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ISR_Pin_PC =   (ISR_Pin_PC & \
                                (uint32)(~(uint32)(ISR_Pin_DRIVE_MODE_IND_MASK << (ISR_Pin_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ISR_Pin_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ISR_Pin_Write
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
void ISR_Pin_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ISR_Pin_DR & (uint8)(~ISR_Pin_MASK));
    drVal = (drVal | ((uint8)(value << ISR_Pin_SHIFT) & ISR_Pin_MASK));
    ISR_Pin_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ISR_Pin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ISR_Pin_DM_STRONG     Strong Drive 
*  ISR_Pin_DM_OD_HI      Open Drain, Drives High 
*  ISR_Pin_DM_OD_LO      Open Drain, Drives Low 
*  ISR_Pin_DM_RES_UP     Resistive Pull Up 
*  ISR_Pin_DM_RES_DWN    Resistive Pull Down 
*  ISR_Pin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ISR_Pin_DM_DIG_HIZ    High Impedance Digital 
*  ISR_Pin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ISR_Pin_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ISR_Pin__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ISR_Pin_Read
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
*  Macro ISR_Pin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ISR_Pin_Read(void) 
{
    return (uint8)((ISR_Pin_PS & ISR_Pin_MASK) >> ISR_Pin_SHIFT);
}


/*******************************************************************************
* Function Name: ISR_Pin_ReadDataReg
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
uint8 ISR_Pin_ReadDataReg(void) 
{
    return (uint8)((ISR_Pin_DR & ISR_Pin_MASK) >> ISR_Pin_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ISR_Pin_INTSTAT) 

    /*******************************************************************************
    * Function Name: ISR_Pin_ClearInterrupt
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
    uint8 ISR_Pin_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ISR_Pin_INTSTAT & ISR_Pin_MASK);
		ISR_Pin_INTSTAT = maskedStatus;
        return maskedStatus >> ISR_Pin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
