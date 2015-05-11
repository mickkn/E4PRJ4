/*******************************************************************************
* File Name: ShutdownSwich.h  
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

#if !defined(CY_PINS_ShutdownSwich_H) /* Pins ShutdownSwich_H */
#define CY_PINS_ShutdownSwich_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ShutdownSwich_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ShutdownSwich_Write(uint8 value) ;
void    ShutdownSwich_SetDriveMode(uint8 mode) ;
uint8   ShutdownSwich_ReadDataReg(void) ;
uint8   ShutdownSwich_Read(void) ;
uint8   ShutdownSwich_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ShutdownSwich_DRIVE_MODE_BITS        (3)
#define ShutdownSwich_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ShutdownSwich_DRIVE_MODE_BITS))

#define ShutdownSwich_DM_ALG_HIZ         (0x00u)
#define ShutdownSwich_DM_DIG_HIZ         (0x01u)
#define ShutdownSwich_DM_RES_UP          (0x02u)
#define ShutdownSwich_DM_RES_DWN         (0x03u)
#define ShutdownSwich_DM_OD_LO           (0x04u)
#define ShutdownSwich_DM_OD_HI           (0x05u)
#define ShutdownSwich_DM_STRONG          (0x06u)
#define ShutdownSwich_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ShutdownSwich_MASK               ShutdownSwich__MASK
#define ShutdownSwich_SHIFT              ShutdownSwich__SHIFT
#define ShutdownSwich_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ShutdownSwich_PS                     (* (reg32 *) ShutdownSwich__PS)
/* Port Configuration */
#define ShutdownSwich_PC                     (* (reg32 *) ShutdownSwich__PC)
/* Data Register */
#define ShutdownSwich_DR                     (* (reg32 *) ShutdownSwich__DR)
/* Input Buffer Disable Override */
#define ShutdownSwich_INP_DIS                (* (reg32 *) ShutdownSwich__PC2)


#if defined(ShutdownSwich__INTSTAT)  /* Interrupt Registers */

    #define ShutdownSwich_INTSTAT                (* (reg32 *) ShutdownSwich__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ShutdownSwich_DRIVE_MODE_SHIFT       (0x00u)
#define ShutdownSwich_DRIVE_MODE_MASK        (0x07u << ShutdownSwich_DRIVE_MODE_SHIFT)


#endif /* End Pins ShutdownSwich_H */


/* [] END OF FILE */
