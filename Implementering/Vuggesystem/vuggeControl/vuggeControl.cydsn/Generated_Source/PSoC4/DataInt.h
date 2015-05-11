/*******************************************************************************
* File Name: DataInt.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DataInt_H) /* Pins DataInt_H */
#define CY_PINS_DataInt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DataInt_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DataInt_Write(uint8 value) ;
void    DataInt_SetDriveMode(uint8 mode) ;
uint8   DataInt_ReadDataReg(void) ;
uint8   DataInt_Read(void) ;
uint8   DataInt_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DataInt_DRIVE_MODE_BITS        (3)
#define DataInt_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DataInt_DRIVE_MODE_BITS))

#define DataInt_DM_ALG_HIZ         (0x00u)
#define DataInt_DM_DIG_HIZ         (0x01u)
#define DataInt_DM_RES_UP          (0x02u)
#define DataInt_DM_RES_DWN         (0x03u)
#define DataInt_DM_OD_LO           (0x04u)
#define DataInt_DM_OD_HI           (0x05u)
#define DataInt_DM_STRONG          (0x06u)
#define DataInt_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define DataInt_MASK               DataInt__MASK
#define DataInt_SHIFT              DataInt__SHIFT
#define DataInt_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DataInt_PS                     (* (reg32 *) DataInt__PS)
/* Port Configuration */
#define DataInt_PC                     (* (reg32 *) DataInt__PC)
/* Data Register */
#define DataInt_DR                     (* (reg32 *) DataInt__DR)
/* Input Buffer Disable Override */
#define DataInt_INP_DIS                (* (reg32 *) DataInt__PC2)


#if defined(DataInt__INTSTAT)  /* Interrupt Registers */

    #define DataInt_INTSTAT                (* (reg32 *) DataInt__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define DataInt_DRIVE_MODE_SHIFT       (0x00u)
#define DataInt_DRIVE_MODE_MASK        (0x07u << DataInt_DRIVE_MODE_SHIFT)


#endif /* End Pins DataInt_H */


/* [] END OF FILE */
