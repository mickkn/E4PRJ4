/*******************************************************************************
* File Name: TestPin.c  
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
#include "TestPin.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TestPin_PC =   (TestPin_PC & \
                                (uint32)(~(uint32)(TestPin_DRIVE_MODE_IND_MASK << (TestPin_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TestPin_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TestPin_Write
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
void TestPin_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TestPin_DR & (uint8)(~TestPin_MASK));
    drVal = (drVal | ((uint8)(value << TestPin_SHIFT) & TestPin_MASK));
    TestPin_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TestPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TestPin_DM_STRONG     Strong Drive 
*  TestPin_DM_OD_HI      Open Drain, Drives High 
*  TestPin_DM_OD_LO      Open Drain, Drives Low 
*  TestPin_DM_RES_UP     Resistive Pull Up 
*  TestPin_DM_RES_DWN    Resistive Pull Down 
*  TestPin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TestPin_DM_DIG_HIZ    High Impedance Digital 
*  TestPin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TestPin_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TestPin__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TestPin_Read
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
*  Macro TestPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TestPin_Read(void) 
{
    return (uint8)((TestPin_PS & TestPin_MASK) >> TestPin_SHIFT);
}


/*******************************************************************************
* Function Name: TestPin_ReadDataReg
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
uint8 TestPin_ReadDataReg(void) 
{
    return (uint8)((TestPin_DR & TestPin_MASK) >> TestPin_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TestPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: TestPin_ClearInterrupt
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
    uint8 TestPin_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TestPin_INTSTAT & TestPin_MASK);
		TestPin_INTSTAT = maskedStatus;
        return maskedStatus >> TestPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
