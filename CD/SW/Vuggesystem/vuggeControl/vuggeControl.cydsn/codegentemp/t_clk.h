/*******************************************************************************
* File Name: t_clk.h
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

#if !defined(CY_CLOCK_t_clk_H)
#define CY_CLOCK_t_clk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void t_clk_StartEx(uint32 alignClkDiv);
#define t_clk_Start() \
    t_clk_StartEx(t_clk__PA_DIV_ID)

#else

void t_clk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void t_clk_Stop(void);

void t_clk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 t_clk_GetDividerRegister(void);
uint8  t_clk_GetFractionalDividerRegister(void);

#define t_clk_Enable()                         t_clk_Start()
#define t_clk_Disable()                        t_clk_Stop()
#define t_clk_SetDividerRegister(clkDivider, reset)  \
    t_clk_SetFractionalDividerRegister((clkDivider), 0u)
#define t_clk_SetDivider(clkDivider)           t_clk_SetDividerRegister((clkDivider), 1u)
#define t_clk_SetDividerValue(clkDivider)      t_clk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define t_clk_DIV_ID     t_clk__DIV_ID

#define t_clk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define t_clk_CTRL_REG   (*(reg32 *)t_clk__CTRL_REGISTER)
#define t_clk_DIV_REG    (*(reg32 *)t_clk__DIV_REGISTER)

#define t_clk_CMD_DIV_SHIFT          (0u)
#define t_clk_CMD_PA_DIV_SHIFT       (8u)
#define t_clk_CMD_DISABLE_SHIFT      (30u)
#define t_clk_CMD_ENABLE_SHIFT       (31u)

#define t_clk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << t_clk_CMD_DISABLE_SHIFT))
#define t_clk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << t_clk_CMD_ENABLE_SHIFT))

#define t_clk_DIV_FRAC_MASK  (0x000000F8u)
#define t_clk_DIV_FRAC_SHIFT (3u)
#define t_clk_DIV_INT_MASK   (0xFFFFFF00u)
#define t_clk_DIV_INT_SHIFT  (8u)

#else 

#define t_clk_DIV_REG        (*(reg32 *)t_clk__REGISTER)
#define t_clk_ENABLE_REG     t_clk_DIV_REG
#define t_clk_DIV_FRAC_MASK  t_clk__FRAC_MASK
#define t_clk_DIV_FRAC_SHIFT (16u)
#define t_clk_DIV_INT_MASK   t_clk__DIVIDER_MASK
#define t_clk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_t_clk_H) */

/* [] END OF FILE */
