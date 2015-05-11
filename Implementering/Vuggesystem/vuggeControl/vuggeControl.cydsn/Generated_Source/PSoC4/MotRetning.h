/*******************************************************************************
* File Name: MotRetning.h  
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

#if !defined(CY_PINS_MotRetning_H) /* Pins MotRetning_H */
#define CY_PINS_MotRetning_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MotRetning_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MotRetning_Write(uint8 value) ;
void    MotRetning_SetDriveMode(uint8 mode) ;
uint8   MotRetning_ReadDataReg(void) ;
uint8   MotRetning_Read(void) ;
uint8   MotRetning_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MotRetning_DRIVE_MODE_BITS        (3)
#define MotRetning_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MotRetning_DRIVE_MODE_BITS))

#define MotRetning_DM_ALG_HIZ         (0x00u)
#define MotRetning_DM_DIG_HIZ         (0x01u)
#define MotRetning_DM_RES_UP          (0x02u)
#define MotRetning_DM_RES_DWN         (0x03u)
#define MotRetning_DM_OD_LO           (0x04u)
#define MotRetning_DM_OD_HI           (0x05u)
#define MotRetning_DM_STRONG          (0x06u)
#define MotRetning_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define MotRetning_MASK               MotRetning__MASK
#define MotRetning_SHIFT              MotRetning__SHIFT
#define MotRetning_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotRetning_PS                     (* (reg32 *) MotRetning__PS)
/* Port Configuration */
#define MotRetning_PC                     (* (reg32 *) MotRetning__PC)
/* Data Register */
#define MotRetning_DR                     (* (reg32 *) MotRetning__DR)
/* Input Buffer Disable Override */
#define MotRetning_INP_DIS                (* (reg32 *) MotRetning__PC2)


#if defined(MotRetning__INTSTAT)  /* Interrupt Registers */

    #define MotRetning_INTSTAT                (* (reg32 *) MotRetning__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define MotRetning_DRIVE_MODE_SHIFT       (0x00u)
#define MotRetning_DRIVE_MODE_MASK        (0x07u << MotRetning_DRIVE_MODE_SHIFT)


#endif /* End Pins MotRetning_H */


/* [] END OF FILE */
