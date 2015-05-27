/*******************************************************************************
* File Name: I2CVuggesystem_scl.c  
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
#include "I2CVuggesystem_scl.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        I2CVuggesystem_scl_PC =   (I2CVuggesystem_scl_PC & \
                                (uint32)(~(uint32)(I2CVuggesystem_scl_DRIVE_MODE_IND_MASK << (I2CVuggesystem_scl_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (I2CVuggesystem_scl_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: I2CVuggesystem_scl_Write
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
void I2CVuggesystem_scl_Write(uint8 value) 
{
    uint8 drVal = (uint8)(I2CVuggesystem_scl_DR & (uint8)(~I2CVuggesystem_scl_MASK));
    drVal = (drVal | ((uint8)(value << I2CVuggesystem_scl_SHIFT) & I2CVuggesystem_scl_MASK));
    I2CVuggesystem_scl_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: I2CVuggesystem_scl_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  I2CVuggesystem_scl_DM_STRONG     Strong Drive 
*  I2CVuggesystem_scl_DM_OD_HI      Open Drain, Drives High 
*  I2CVuggesystem_scl_DM_OD_LO      Open Drain, Drives Low 
*  I2CVuggesystem_scl_DM_RES_UP     Resistive Pull Up 
*  I2CVuggesystem_scl_DM_RES_DWN    Resistive Pull Down 
*  I2CVuggesystem_scl_DM_RES_UPDWN  Resistive Pull Up/Down 
*  I2CVuggesystem_scl_DM_DIG_HIZ    High Impedance Digital 
*  I2CVuggesystem_scl_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void I2CVuggesystem_scl_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(I2CVuggesystem_scl__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: I2CVuggesystem_scl_Read
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
*  Macro I2CVuggesystem_scl_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 I2CVuggesystem_scl_Read(void) 
{
    return (uint8)((I2CVuggesystem_scl_PS & I2CVuggesystem_scl_MASK) >> I2CVuggesystem_scl_SHIFT);
}


/*******************************************************************************
* Function Name: I2CVuggesystem_scl_ReadDataReg
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
uint8 I2CVuggesystem_scl_ReadDataReg(void) 
{
    return (uint8)((I2CVuggesystem_scl_DR & I2CVuggesystem_scl_MASK) >> I2CVuggesystem_scl_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(I2CVuggesystem_scl_INTSTAT) 

    /*******************************************************************************
    * Function Name: I2CVuggesystem_scl_ClearInterrupt
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
    uint8 I2CVuggesystem_scl_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(I2CVuggesystem_scl_INTSTAT & I2CVuggesystem_scl_MASK);
		I2CVuggesystem_scl_INTSTAT = maskedStatus;
        return maskedStatus >> I2CVuggesystem_scl_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
