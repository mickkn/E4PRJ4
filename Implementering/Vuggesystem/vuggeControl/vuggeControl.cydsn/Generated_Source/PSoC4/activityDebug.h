/*******************************************************************************
* File Name: activityDebug.h  
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

#if !defined(CY_PINS_activityDebug_H) /* Pins activityDebug_H */
#define CY_PINS_activityDebug_H

#include "cytypes.h"
#include "cyfitter.h"
#include "activityDebug_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    activityDebug_Write(uint8 value) ;
void    activityDebug_SetDriveMode(uint8 mode) ;
uint8   activityDebug_ReadDataReg(void) ;
uint8   activityDebug_Read(void) ;
uint8   activityDebug_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define activityDebug_DRIVE_MODE_BITS        (3)
#define activityDebug_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - activityDebug_DRIVE_MODE_BITS))

#define activityDebug_DM_ALG_HIZ         (0x00u)
#define activityDebug_DM_DIG_HIZ         (0x01u)
#define activityDebug_DM_RES_UP          (0x02u)
#define activityDebug_DM_RES_DWN         (0x03u)
#define activityDebug_DM_OD_LO           (0x04u)
#define activityDebug_DM_OD_HI           (0x05u)
#define activityDebug_DM_STRONG          (0x06u)
#define activityDebug_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define activityDebug_MASK               activityDebug__MASK
#define activityDebug_SHIFT              activityDebug__SHIFT
#define activityDebug_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define activityDebug_PS                     (* (reg32 *) activityDebug__PS)
/* Port Configuration */
#define activityDebug_PC                     (* (reg32 *) activityDebug__PC)
/* Data Register */
#define activityDebug_DR                     (* (reg32 *) activityDebug__DR)
/* Input Buffer Disable Override */
#define activityDebug_INP_DIS                (* (reg32 *) activityDebug__PC2)


#if defined(activityDebug__INTSTAT)  /* Interrupt Registers */

    #define activityDebug_INTSTAT                (* (reg32 *) activityDebug__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define activityDebug_DRIVE_MODE_SHIFT       (0x00u)
#define activityDebug_DRIVE_MODE_MASK        (0x07u << activityDebug_DRIVE_MODE_SHIFT)


#endif /* End Pins activityDebug_H */


/* [] END OF FILE */
