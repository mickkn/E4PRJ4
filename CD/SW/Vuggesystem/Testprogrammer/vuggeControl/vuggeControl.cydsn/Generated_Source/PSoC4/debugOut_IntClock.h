/*******************************************************************************
* File Name: debugOut_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_debugOut_IntClock_H)
#define CY_CLOCK_debugOut_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void debugOut_IntClock_StartEx(uint32 alignClkDiv);
#define debugOut_IntClock_Start() \
    debugOut_IntClock_StartEx(debugOut_IntClock__PA_DIV_ID)

#else

void debugOut_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void debugOut_IntClock_Stop(void);

void debugOut_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 debugOut_IntClock_GetDividerRegister(void);
uint8  debugOut_IntClock_GetFractionalDividerRegister(void);

#define debugOut_IntClock_Enable()                         debugOut_IntClock_Start()
#define debugOut_IntClock_Disable()                        debugOut_IntClock_Stop()
#define debugOut_IntClock_SetDividerRegister(clkDivider, reset)  \
    debugOut_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define debugOut_IntClock_SetDivider(clkDivider)           debugOut_IntClock_SetDividerRegister((clkDivider), 1u)
#define debugOut_IntClock_SetDividerValue(clkDivider)      debugOut_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define debugOut_IntClock_DIV_ID     debugOut_IntClock__DIV_ID

#define debugOut_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define debugOut_IntClock_CTRL_REG   (*(reg32 *)debugOut_IntClock__CTRL_REGISTER)
#define debugOut_IntClock_DIV_REG    (*(reg32 *)debugOut_IntClock__DIV_REGISTER)

#define debugOut_IntClock_CMD_DIV_SHIFT          (0u)
#define debugOut_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define debugOut_IntClock_CMD_DISABLE_SHIFT      (30u)
#define debugOut_IntClock_CMD_ENABLE_SHIFT       (31u)

#define debugOut_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << debugOut_IntClock_CMD_DISABLE_SHIFT))
#define debugOut_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << debugOut_IntClock_CMD_ENABLE_SHIFT))

#define debugOut_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define debugOut_IntClock_DIV_FRAC_SHIFT (3u)
#define debugOut_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define debugOut_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define debugOut_IntClock_DIV_REG        (*(reg32 *)debugOut_IntClock__REGISTER)
#define debugOut_IntClock_ENABLE_REG     debugOut_IntClock_DIV_REG
#define debugOut_IntClock_DIV_FRAC_MASK  debugOut_IntClock__FRAC_MASK
#define debugOut_IntClock_DIV_FRAC_SHIFT (16u)
#define debugOut_IntClock_DIV_INT_MASK   debugOut_IntClock__DIVIDER_MASK
#define debugOut_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_debugOut_IntClock_H) */

/* [] END OF FILE */
