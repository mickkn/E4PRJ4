/*******************************************************************************
* File Name: TestPin.h  
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

#if !defined(CY_PINS_TestPin_H) /* Pins TestPin_H */
#define CY_PINS_TestPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TestPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TestPin_Write(uint8 value) ;
void    TestPin_SetDriveMode(uint8 mode) ;
uint8   TestPin_ReadDataReg(void) ;
uint8   TestPin_Read(void) ;
uint8   TestPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TestPin_DRIVE_MODE_BITS        (3)
#define TestPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TestPin_DRIVE_MODE_BITS))

#define TestPin_DM_ALG_HIZ         (0x00u)
#define TestPin_DM_DIG_HIZ         (0x01u)
#define TestPin_DM_RES_UP          (0x02u)
#define TestPin_DM_RES_DWN         (0x03u)
#define TestPin_DM_OD_LO           (0x04u)
#define TestPin_DM_OD_HI           (0x05u)
#define TestPin_DM_STRONG          (0x06u)
#define TestPin_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TestPin_MASK               TestPin__MASK
#define TestPin_SHIFT              TestPin__SHIFT
#define TestPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TestPin_PS                     (* (reg32 *) TestPin__PS)
/* Port Configuration */
#define TestPin_PC                     (* (reg32 *) TestPin__PC)
/* Data Register */
#define TestPin_DR                     (* (reg32 *) TestPin__DR)
/* Input Buffer Disable Override */
#define TestPin_INP_DIS                (* (reg32 *) TestPin__PC2)


#if defined(TestPin__INTSTAT)  /* Interrupt Registers */

    #define TestPin_INTSTAT                (* (reg32 *) TestPin__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TestPin_DRIVE_MODE_SHIFT       (0x00u)
#define TestPin_DRIVE_MODE_MASK        (0x07u << TestPin_DRIVE_MODE_SHIFT)


#endif /* End Pins TestPin_H */


/* [] END OF FILE */
