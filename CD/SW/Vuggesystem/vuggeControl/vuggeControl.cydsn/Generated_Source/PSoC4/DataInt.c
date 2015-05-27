/*******************************************************************************
* File Name: DataInt.c  
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
#include "DataInt.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DataInt_PC =   (DataInt_PC & \
                                (uint32)(~(uint32)(DataInt_DRIVE_MODE_IND_MASK << (DataInt_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DataInt_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DataInt_Write
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
void DataInt_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DataInt_DR & (uint8)(~DataInt_MASK));
    drVal = (drVal | ((uint8)(value << DataInt_SHIFT) & DataInt_MASK));
    DataInt_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DataInt_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DataInt_DM_STRONG     Strong Drive 
*  DataInt_DM_OD_HI      Open Drain, Drives High 
*  DataInt_DM_OD_LO      Open Drain, Drives Low 
*  DataInt_DM_RES_UP     Resistive Pull Up 
*  DataInt_DM_RES_DWN    Resistive Pull Down 
*  DataInt_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DataInt_DM_DIG_HIZ    High Impedance Digital 
*  DataInt_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DataInt_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DataInt__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DataInt_Read
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
*  Macro DataInt_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DataInt_Read(void) 
{
    return (uint8)((DataInt_PS & DataInt_MASK) >> DataInt_SHIFT);
}


/*******************************************************************************
* Function Name: DataInt_ReadDataReg
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
uint8 DataInt_ReadDataReg(void) 
{
    return (uint8)((DataInt_DR & DataInt_MASK) >> DataInt_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DataInt_INTSTAT) 

    /*******************************************************************************
    * Function Name: DataInt_ClearInterrupt
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
    uint8 DataInt_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DataInt_INTSTAT & DataInt_MASK);
		DataInt_INTSTAT = maskedStatus;
        return maskedStatus >> DataInt_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
