/*******************************************************************************
* File Name: ACC_DR.h  
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

#if !defined(CY_PINS_ACC_DR_H) /* Pins ACC_DR_H */
#define CY_PINS_ACC_DR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ACC_DR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ACC_DR_Write(uint8 value) ;
void    ACC_DR_SetDriveMode(uint8 mode) ;
uint8   ACC_DR_ReadDataReg(void) ;
uint8   ACC_DR_Read(void) ;
uint8   ACC_DR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ACC_DR_DRIVE_MODE_BITS        (3)
#define ACC_DR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ACC_DR_DRIVE_MODE_BITS))

#define ACC_DR_DM_ALG_HIZ         (0x00u)
#define ACC_DR_DM_DIG_HIZ         (0x01u)
#define ACC_DR_DM_RES_UP          (0x02u)
#define ACC_DR_DM_RES_DWN         (0x03u)
#define ACC_DR_DM_OD_LO           (0x04u)
#define ACC_DR_DM_OD_HI           (0x05u)
#define ACC_DR_DM_STRONG          (0x06u)
#define ACC_DR_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ACC_DR_MASK               ACC_DR__MASK
#define ACC_DR_SHIFT              ACC_DR__SHIFT
#define ACC_DR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ACC_DR_PS                     (* (reg32 *) ACC_DR__PS)
/* Port Configuration */
#define ACC_DR_PC                     (* (reg32 *) ACC_DR__PC)
/* Data Register */
#define ACC_DR_DR                     (* (reg32 *) ACC_DR__DR)
/* Input Buffer Disable Override */
#define ACC_DR_INP_DIS                (* (reg32 *) ACC_DR__PC2)


#if defined(ACC_DR__INTSTAT)  /* Interrupt Registers */

    #define ACC_DR_INTSTAT                (* (reg32 *) ACC_DR__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ACC_DR_DRIVE_MODE_SHIFT       (0x00u)
#define ACC_DR_DRIVE_MODE_MASK        (0x07u << ACC_DR_DRIVE_MODE_SHIFT)


#endif /* End Pins ACC_DR_H */


/* [] END OF FILE */
