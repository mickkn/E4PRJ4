/*******************************************************************************
* File Name: GYRO_DR.h  
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

#if !defined(CY_PINS_GYRO_DR_H) /* Pins GYRO_DR_H */
#define CY_PINS_GYRO_DR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GYRO_DR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GYRO_DR_Write(uint8 value) ;
void    GYRO_DR_SetDriveMode(uint8 mode) ;
uint8   GYRO_DR_ReadDataReg(void) ;
uint8   GYRO_DR_Read(void) ;
uint8   GYRO_DR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GYRO_DR_DRIVE_MODE_BITS        (3)
#define GYRO_DR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GYRO_DR_DRIVE_MODE_BITS))

#define GYRO_DR_DM_ALG_HIZ         (0x00u)
#define GYRO_DR_DM_DIG_HIZ         (0x01u)
#define GYRO_DR_DM_RES_UP          (0x02u)
#define GYRO_DR_DM_RES_DWN         (0x03u)
#define GYRO_DR_DM_OD_LO           (0x04u)
#define GYRO_DR_DM_OD_HI           (0x05u)
#define GYRO_DR_DM_STRONG          (0x06u)
#define GYRO_DR_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define GYRO_DR_MASK               GYRO_DR__MASK
#define GYRO_DR_SHIFT              GYRO_DR__SHIFT
#define GYRO_DR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GYRO_DR_PS                     (* (reg32 *) GYRO_DR__PS)
/* Port Configuration */
#define GYRO_DR_PC                     (* (reg32 *) GYRO_DR__PC)
/* Data Register */
#define GYRO_DR_DR                     (* (reg32 *) GYRO_DR__DR)
/* Input Buffer Disable Override */
#define GYRO_DR_INP_DIS                (* (reg32 *) GYRO_DR__PC2)


#if defined(GYRO_DR__INTSTAT)  /* Interrupt Registers */

    #define GYRO_DR_INTSTAT                (* (reg32 *) GYRO_DR__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define GYRO_DR_DRIVE_MODE_SHIFT       (0x00u)
#define GYRO_DR_DRIVE_MODE_MASK        (0x07u << GYRO_DR_DRIVE_MODE_SHIFT)


#endif /* End Pins GYRO_DR_H */


/* [] END OF FILE */
