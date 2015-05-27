/*******************************************************************************
* File Name: sensorI2C_scl.c  
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
#include "sensorI2C_scl.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        sensorI2C_scl_PC =   (sensorI2C_scl_PC & \
                                (uint32)(~(uint32)(sensorI2C_scl_DRIVE_MODE_IND_MASK << (sensorI2C_scl_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (sensorI2C_scl_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: sensorI2C_scl_Write
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
void sensorI2C_scl_Write(uint8 value) 
{
    uint8 drVal = (uint8)(sensorI2C_scl_DR & (uint8)(~sensorI2C_scl_MASK));
    drVal = (drVal | ((uint8)(value << sensorI2C_scl_SHIFT) & sensorI2C_scl_MASK));
    sensorI2C_scl_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: sensorI2C_scl_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  sensorI2C_scl_DM_STRONG     Strong Drive 
*  sensorI2C_scl_DM_OD_HI      Open Drain, Drives High 
*  sensorI2C_scl_DM_OD_LO      Open Drain, Drives Low 
*  sensorI2C_scl_DM_RES_UP     Resistive Pull Up 
*  sensorI2C_scl_DM_RES_DWN    Resistive Pull Down 
*  sensorI2C_scl_DM_RES_UPDWN  Resistive Pull Up/Down 
*  sensorI2C_scl_DM_DIG_HIZ    High Impedance Digital 
*  sensorI2C_scl_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void sensorI2C_scl_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(sensorI2C_scl__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: sensorI2C_scl_Read
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
*  Macro sensorI2C_scl_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 sensorI2C_scl_Read(void) 
{
    return (uint8)((sensorI2C_scl_PS & sensorI2C_scl_MASK) >> sensorI2C_scl_SHIFT);
}


/*******************************************************************************
* Function Name: sensorI2C_scl_ReadDataReg
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
uint8 sensorI2C_scl_ReadDataReg(void) 
{
    return (uint8)((sensorI2C_scl_DR & sensorI2C_scl_MASK) >> sensorI2C_scl_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(sensorI2C_scl_INTSTAT) 

    /*******************************************************************************
    * Function Name: sensorI2C_scl_ClearInterrupt
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
    uint8 sensorI2C_scl_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(sensorI2C_scl_INTSTAT & sensorI2C_scl_MASK);
		sensorI2C_scl_INTSTAT = maskedStatus;
        return maskedStatus >> sensorI2C_scl_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
