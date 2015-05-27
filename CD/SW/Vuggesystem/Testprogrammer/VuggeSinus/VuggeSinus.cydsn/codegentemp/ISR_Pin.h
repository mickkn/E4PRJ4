/*******************************************************************************
* File Name: ISR_Pin.h  
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

#if !defined(CY_PINS_ISR_Pin_H) /* Pins ISR_Pin_H */
#define CY_PINS_ISR_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ISR_Pin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ISR_Pin_Write(uint8 value) ;
void    ISR_Pin_SetDriveMode(uint8 mode) ;
uint8   ISR_Pin_ReadDataReg(void) ;
uint8   ISR_Pin_Read(void) ;
uint8   ISR_Pin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ISR_Pin_DRIVE_MODE_BITS        (3)
#define ISR_Pin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ISR_Pin_DRIVE_MODE_BITS))

#define ISR_Pin_DM_ALG_HIZ         (0x00u)
#define ISR_Pin_DM_DIG_HIZ         (0x01u)
#define ISR_Pin_DM_RES_UP          (0x02u)
#define ISR_Pin_DM_RES_DWN         (0x03u)
#define ISR_Pin_DM_OD_LO           (0x04u)
#define ISR_Pin_DM_OD_HI           (0x05u)
#define ISR_Pin_DM_STRONG          (0x06u)
#define ISR_Pin_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ISR_Pin_MASK               ISR_Pin__MASK
#define ISR_Pin_SHIFT              ISR_Pin__SHIFT
#define ISR_Pin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ISR_Pin_PS                     (* (reg32 *) ISR_Pin__PS)
/* Port Configuration */
#define ISR_Pin_PC                     (* (reg32 *) ISR_Pin__PC)
/* Data Register */
#define ISR_Pin_DR                     (* (reg32 *) ISR_Pin__DR)
/* Input Buffer Disable Override */
#define ISR_Pin_INP_DIS                (* (reg32 *) ISR_Pin__PC2)


#if defined(ISR_Pin__INTSTAT)  /* Interrupt Registers */

    #define ISR_Pin_INTSTAT                (* (reg32 *) ISR_Pin__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ISR_Pin_DRIVE_MODE_SHIFT       (0x00u)
#define ISR_Pin_DRIVE_MODE_MASK        (0x07u << ISR_Pin_DRIVE_MODE_SHIFT)


#endif /* End Pins ISR_Pin_H */


/* [] END OF FILE */
