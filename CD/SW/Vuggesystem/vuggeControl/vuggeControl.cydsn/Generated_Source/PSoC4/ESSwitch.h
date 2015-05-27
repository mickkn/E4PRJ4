/*******************************************************************************
* File Name: ESSwitch.h  
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

#if !defined(CY_PINS_ESSwitch_H) /* Pins ESSwitch_H */
#define CY_PINS_ESSwitch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ESSwitch_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ESSwitch_Write(uint8 value) ;
void    ESSwitch_SetDriveMode(uint8 mode) ;
uint8   ESSwitch_ReadDataReg(void) ;
uint8   ESSwitch_Read(void) ;
uint8   ESSwitch_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ESSwitch_DRIVE_MODE_BITS        (3)
#define ESSwitch_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ESSwitch_DRIVE_MODE_BITS))

#define ESSwitch_DM_ALG_HIZ         (0x00u)
#define ESSwitch_DM_DIG_HIZ         (0x01u)
#define ESSwitch_DM_RES_UP          (0x02u)
#define ESSwitch_DM_RES_DWN         (0x03u)
#define ESSwitch_DM_OD_LO           (0x04u)
#define ESSwitch_DM_OD_HI           (0x05u)
#define ESSwitch_DM_STRONG          (0x06u)
#define ESSwitch_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ESSwitch_MASK               ESSwitch__MASK
#define ESSwitch_SHIFT              ESSwitch__SHIFT
#define ESSwitch_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ESSwitch_PS                     (* (reg32 *) ESSwitch__PS)
/* Port Configuration */
#define ESSwitch_PC                     (* (reg32 *) ESSwitch__PC)
/* Data Register */
#define ESSwitch_DR                     (* (reg32 *) ESSwitch__DR)
/* Input Buffer Disable Override */
#define ESSwitch_INP_DIS                (* (reg32 *) ESSwitch__PC2)


#if defined(ESSwitch__INTSTAT)  /* Interrupt Registers */

    #define ESSwitch_INTSTAT                (* (reg32 *) ESSwitch__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ESSwitch_DRIVE_MODE_SHIFT       (0x00u)
#define ESSwitch_DRIVE_MODE_MASK        (0x07u << ESSwitch_DRIVE_MODE_SHIFT)


#endif /* End Pins ESSwitch_H */


/* [] END OF FILE */
