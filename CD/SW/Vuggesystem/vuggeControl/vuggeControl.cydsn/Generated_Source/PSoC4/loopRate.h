/*******************************************************************************
* File Name: loopRate.h  
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

#if !defined(CY_PINS_loopRate_H) /* Pins loopRate_H */
#define CY_PINS_loopRate_H

#include "cytypes.h"
#include "cyfitter.h"
#include "loopRate_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    loopRate_Write(uint8 value) ;
void    loopRate_SetDriveMode(uint8 mode) ;
uint8   loopRate_ReadDataReg(void) ;
uint8   loopRate_Read(void) ;
uint8   loopRate_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define loopRate_DRIVE_MODE_BITS        (3)
#define loopRate_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - loopRate_DRIVE_MODE_BITS))

#define loopRate_DM_ALG_HIZ         (0x00u)
#define loopRate_DM_DIG_HIZ         (0x01u)
#define loopRate_DM_RES_UP          (0x02u)
#define loopRate_DM_RES_DWN         (0x03u)
#define loopRate_DM_OD_LO           (0x04u)
#define loopRate_DM_OD_HI           (0x05u)
#define loopRate_DM_STRONG          (0x06u)
#define loopRate_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define loopRate_MASK               loopRate__MASK
#define loopRate_SHIFT              loopRate__SHIFT
#define loopRate_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define loopRate_PS                     (* (reg32 *) loopRate__PS)
/* Port Configuration */
#define loopRate_PC                     (* (reg32 *) loopRate__PC)
/* Data Register */
#define loopRate_DR                     (* (reg32 *) loopRate__DR)
/* Input Buffer Disable Override */
#define loopRate_INP_DIS                (* (reg32 *) loopRate__PC2)


#if defined(loopRate__INTSTAT)  /* Interrupt Registers */

    #define loopRate_INTSTAT                (* (reg32 *) loopRate__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define loopRate_DRIVE_MODE_SHIFT       (0x00u)
#define loopRate_DRIVE_MODE_MASK        (0x07u << loopRate_DRIVE_MODE_SHIFT)


#endif /* End Pins loopRate_H */


/* [] END OF FILE */
