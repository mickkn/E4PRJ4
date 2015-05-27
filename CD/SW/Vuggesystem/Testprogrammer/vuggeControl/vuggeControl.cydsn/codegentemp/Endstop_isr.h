/*******************************************************************************
* File Name: Endstop_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Endstop_isr_H)
#define CY_ISR_Endstop_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Endstop_isr_Start(void);
void Endstop_isr_StartEx(cyisraddress address);
void Endstop_isr_Stop(void);

CY_ISR_PROTO(Endstop_isr_Interrupt);

void Endstop_isr_SetVector(cyisraddress address);
cyisraddress Endstop_isr_GetVector(void);

void Endstop_isr_SetPriority(uint8 priority);
uint8 Endstop_isr_GetPriority(void);

void Endstop_isr_Enable(void);
uint8 Endstop_isr_GetState(void);
void Endstop_isr_Disable(void);

void Endstop_isr_SetPending(void);
void Endstop_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Endstop_isr ISR. */
#define Endstop_isr_INTC_VECTOR            ((reg32 *) Endstop_isr__INTC_VECT)

/* Address of the Endstop_isr ISR priority. */
#define Endstop_isr_INTC_PRIOR             ((reg32 *) Endstop_isr__INTC_PRIOR_REG)

/* Priority of the Endstop_isr interrupt. */
#define Endstop_isr_INTC_PRIOR_NUMBER      Endstop_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Endstop_isr interrupt. */
#define Endstop_isr_INTC_SET_EN            ((reg32 *) Endstop_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Endstop_isr interrupt. */
#define Endstop_isr_INTC_CLR_EN            ((reg32 *) Endstop_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Endstop_isr interrupt state to pending. */
#define Endstop_isr_INTC_SET_PD            ((reg32 *) Endstop_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Endstop_isr interrupt. */
#define Endstop_isr_INTC_CLR_PD            ((reg32 *) Endstop_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_Endstop_isr_H */


/* [] END OF FILE */
