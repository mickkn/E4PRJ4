/*******************************************************************************
* File Name: sensorI2C_PINS.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_sensorI2C_H)
#define CY_SCB_PINS_sensorI2C_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define sensorI2C_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define sensorI2C_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define sensorI2C_REMOVE_MISO_SDA_TX_PIN         (1u)
#define sensorI2C_REMOVE_SCLK_PIN                (1u)
#define sensorI2C_REMOVE_SS0_PIN                 (1u)
#define sensorI2C_REMOVE_SS1_PIN                 (1u)
#define sensorI2C_REMOVE_SS2_PIN                 (1u)
#define sensorI2C_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define sensorI2C_REMOVE_I2C_PINS                (0u)
#define sensorI2C_REMOVE_SPI_MASTER_PINS         (1u)
#define sensorI2C_REMOVE_SPI_SLAVE_PINS          (1u)
#define sensorI2C_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define sensorI2C_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define sensorI2C_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define sensorI2C_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define sensorI2C_REMOVE_UART_TX_PIN             (1u)
#define sensorI2C_REMOVE_UART_RX_TX_PIN          (1u)
#define sensorI2C_REMOVE_UART_RX_PIN             (1u)
#define sensorI2C_REMOVE_UART_RX_WAKE_PIN        (1u)
#define sensorI2C_REMOVE_UART_RTS_PIN            (1u)
#define sensorI2C_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define sensorI2C_MOSI_SCL_RX_WAKE_PIN   (0u == sensorI2C_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define sensorI2C_MOSI_SCL_RX_PIN        (0u == sensorI2C_REMOVE_MOSI_SCL_RX_PIN)
#define sensorI2C_MISO_SDA_TX_PIN        (0u == sensorI2C_REMOVE_MISO_SDA_TX_PIN)
#define sensorI2C_SCLK_PIN               (0u == sensorI2C_REMOVE_SCLK_PIN)
#define sensorI2C_SS0_PIN                (0u == sensorI2C_REMOVE_SS0_PIN)
#define sensorI2C_SS1_PIN                (0u == sensorI2C_REMOVE_SS1_PIN)
#define sensorI2C_SS2_PIN                (0u == sensorI2C_REMOVE_SS2_PIN)
#define sensorI2C_SS3_PIN                (0u == sensorI2C_REMOVE_SS3_PIN)

/* Mode defined pins */
#define sensorI2C_I2C_PINS               (0u == sensorI2C_REMOVE_I2C_PINS)
#define sensorI2C_SPI_MASTER_PINS        (0u == sensorI2C_REMOVE_SPI_MASTER_PINS)
#define sensorI2C_SPI_SLAVE_PINS         (0u == sensorI2C_REMOVE_SPI_SLAVE_PINS)
#define sensorI2C_SPI_MASTER_SS0_PIN     (0u == sensorI2C_REMOVE_SPI_MASTER_SS0_PIN)
#define sensorI2C_SPI_MASTER_SS1_PIN     (0u == sensorI2C_REMOVE_SPI_MASTER_SS1_PIN)
#define sensorI2C_SPI_MASTER_SS2_PIN     (0u == sensorI2C_REMOVE_SPI_MASTER_SS2_PIN)
#define sensorI2C_SPI_MASTER_SS3_PIN     (0u == sensorI2C_REMOVE_SPI_MASTER_SS3_PIN)
#define sensorI2C_UART_TX_PIN            (0u == sensorI2C_REMOVE_UART_TX_PIN)
#define sensorI2C_UART_RX_TX_PIN         (0u == sensorI2C_REMOVE_UART_RX_TX_PIN)
#define sensorI2C_UART_RX_PIN            (0u == sensorI2C_REMOVE_UART_RX_PIN)
#define sensorI2C_UART_RX_WAKE_PIN       (0u == sensorI2C_REMOVE_UART_RX_WAKE_PIN)
#define sensorI2C_UART_RTS_PIN           (0u == sensorI2C_REMOVE_UART_RTS_PIN)
#define sensorI2C_UART_CTS_PIN           (0u == sensorI2C_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if(sensorI2C_MOSI_SCL_RX_WAKE_PIN)
    #include "sensorI2C_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (sensorI2C_MOSI_SCL_RX_WAKE_PIN) */

#if(sensorI2C_MOSI_SCL_RX_PIN)
    #include "sensorI2C_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

#if(sensorI2C_MISO_SDA_TX_PIN)
    #include "sensorI2C_spi_miso_i2c_sda_uart_tx.h"
#endif /* (sensorI2C_MISO_SDA_TX_PIN_PIN) */

#if(sensorI2C_SCLK_PIN)
    #include "sensorI2C_spi_sclk.h"
#endif /* (sensorI2C_SCLK_PIN) */

#if(sensorI2C_SS0_PIN)
    #include "sensorI2C_spi_ss0.h"
#endif /* (sensorI2C_SS1_PIN) */

#if(sensorI2C_SS1_PIN)
    #include "sensorI2C_spi_ss1.h"
#endif /* (sensorI2C_SS1_PIN) */

#if(sensorI2C_SS2_PIN)
    #include "sensorI2C_spi_ss2.h"
#endif /* (sensorI2C_SS2_PIN) */

#if(sensorI2C_SS3_PIN)
    #include "sensorI2C_spi_ss3.h"
#endif /* (sensorI2C_SS3_PIN) */

#if(sensorI2C_I2C_PINS)
    #include "sensorI2C_scl.h"
    #include "sensorI2C_sda.h"
#endif /* (sensorI2C_I2C_PINS) */

#if(sensorI2C_SPI_MASTER_PINS)
    #include "sensorI2C_sclk_m.h"
    #include "sensorI2C_mosi_m.h"
    #include "sensorI2C_miso_m.h"
#endif /* (sensorI2C_SPI_MASTER_PINS) */

#if(sensorI2C_SPI_SLAVE_PINS)
    #include "sensorI2C_sclk_s.h"
    #include "sensorI2C_mosi_s.h"
    #include "sensorI2C_miso_s.h"
    #include "sensorI2C_ss_s.h"
#endif /* (sensorI2C_SPI_SLAVE_PINS) */

#if(sensorI2C_SPI_MASTER_SS0_PIN)
    #include "sensorI2C_ss0_m.h"
#endif /* (sensorI2C_SPI_MASTER_SS0_PIN) */

#if(sensorI2C_SPI_MASTER_SS1_PIN)
    #include "sensorI2C_ss1_m.h"
#endif /* (sensorI2C_SPI_MASTER_SS1_PIN) */

#if(sensorI2C_SPI_MASTER_SS2_PIN)
    #include "sensorI2C_ss2_m.h"
#endif /* (sensorI2C_SPI_MASTER_SS2_PIN) */

#if(sensorI2C_SPI_MASTER_SS3_PIN)
    #include "sensorI2C_ss3_m.h"
#endif /* (sensorI2C_SPI_MASTER_SS3_PIN) */

#if(sensorI2C_UART_TX_PIN)
    #include "sensorI2C_tx.h"
#endif /* (sensorI2C_UART_TX_PIN) */

#if(sensorI2C_UART_RX_TX_PIN)
    #include "sensorI2C_rx_tx.h"
#endif /* (sensorI2C_UART_RX_TX_PIN) */

#if(sensorI2C_UART_RX_PIN)
    #include "sensorI2C_rx.h"
#endif /* (sensorI2C_UART_RX_PIN) */

#if(sensorI2C_UART_RX_WAKE_PIN)
    #include "sensorI2C_rx_wake.h"
#endif /* (sensorI2C_UART_RX_WAKE_PIN) */

#if(sensorI2C_UART_RTS_PIN)
    #include "sensorI2C_rts.h"
#endif /* (sensorI2C_UART_RTS_PIN) */

#if(sensorI2C_UART_CTS_PIN)
    #include "sensorI2C_cts.h"
#endif /* (sensorI2C_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if(sensorI2C_MOSI_SCL_RX_WAKE_PIN)
    #define sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define sensorI2C_INTCFG_TYPE_MASK                  (0x03u)
    #define sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (sensorI2C_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) sensorI2C_INTCFG_TYPE_MASK << \
                                                                    sensorI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (sensorI2C_MOSI_SCL_RX_WAKE_PIN) */

#if(sensorI2C_MOSI_SCL_RX_PIN)
    #define sensorI2C_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) sensorI2C_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define sensorI2C_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) sensorI2C_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define sensorI2C_MOSI_SCL_RX_HSIOM_MASK     (sensorI2C_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define sensorI2C_MOSI_SCL_RX_HSIOM_POS      (sensorI2C_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

#if(sensorI2C_MISO_SDA_TX_PIN)
    #define sensorI2C_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) sensorI2C_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define sensorI2C_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) sensorI2C_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define sensorI2C_MISO_SDA_TX_HSIOM_MASK     (sensorI2C_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define sensorI2C_MISO_SDA_TX_HSIOM_POS      (sensorI2C_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (sensorI2C_MISO_SDA_TX_PIN_PIN) */

#if(sensorI2C_SCLK_PIN)
    #define sensorI2C_SCLK_HSIOM_REG     (*(reg32 *) sensorI2C_spi_sclk__0__HSIOM)
    #define sensorI2C_SCLK_HSIOM_PTR     ( (reg32 *) sensorI2C_spi_sclk__0__HSIOM)
    #define sensorI2C_SCLK_HSIOM_MASK    (sensorI2C_spi_sclk__0__HSIOM_MASK)
    #define sensorI2C_SCLK_HSIOM_POS     (sensorI2C_spi_sclk__0__HSIOM_SHIFT)
#endif /* (sensorI2C_SCLK_PIN) */

#if(sensorI2C_SS0_PIN)
    #define sensorI2C_SS0_HSIOM_REG      (*(reg32 *) sensorI2C_spi_ss0__0__HSIOM)
    #define sensorI2C_SS0_HSIOM_PTR      ( (reg32 *) sensorI2C_spi_ss0__0__HSIOM)
    #define sensorI2C_SS0_HSIOM_MASK     (sensorI2C_spi_ss0__0__HSIOM_MASK)
    #define sensorI2C_SS0_HSIOM_POS      (sensorI2C_spi_ss0__0__HSIOM_SHIFT)
#endif /* (sensorI2C_SS1_PIN) */

#if(sensorI2C_SS1_PIN)
    #define sensorI2C_SS1_HSIOM_REG      (*(reg32 *) sensorI2C_spi_ss1__0__HSIOM)
    #define sensorI2C_SS1_HSIOM_PTR      ( (reg32 *) sensorI2C_spi_ss1__0__HSIOM)
    #define sensorI2C_SS1_HSIOM_MASK     (sensorI2C_spi_ss1__0__HSIOM_MASK)
    #define sensorI2C_SS1_HSIOM_POS      (sensorI2C_spi_ss1__0__HSIOM_SHIFT)
#endif /* (sensorI2C_SS1_PIN) */

#if(sensorI2C_SS2_PIN)
    #define sensorI2C_SS2_HSIOM_REG     (*(reg32 *) sensorI2C_spi_ss2__0__HSIOM)
    #define sensorI2C_SS2_HSIOM_PTR     ( (reg32 *) sensorI2C_spi_ss2__0__HSIOM)
    #define sensorI2C_SS2_HSIOM_MASK    (sensorI2C_spi_ss2__0__HSIOM_MASK)
    #define sensorI2C_SS2_HSIOM_POS     (sensorI2C_spi_ss2__0__HSIOM_SHIFT)
#endif /* (sensorI2C_SS2_PIN) */

#if(sensorI2C_SS3_PIN)
    #define sensorI2C_SS3_HSIOM_REG     (*(reg32 *) sensorI2C_spi_ss3__0__HSIOM)
    #define sensorI2C_SS3_HSIOM_PTR     ( (reg32 *) sensorI2C_spi_ss3__0__HSIOM)
    #define sensorI2C_SS3_HSIOM_MASK    (sensorI2C_spi_ss3__0__HSIOM_MASK)
    #define sensorI2C_SS3_HSIOM_POS     (sensorI2C_spi_ss3__0__HSIOM_SHIFT)
#endif /* (sensorI2C_SS3_PIN) */

#if(sensorI2C_I2C_PINS)
    #define sensorI2C_SCL_HSIOM_REG     (*(reg32 *) sensorI2C_scl__0__HSIOM)
    #define sensorI2C_SCL_HSIOM_PTR     ( (reg32 *) sensorI2C_scl__0__HSIOM)
    #define sensorI2C_SCL_HSIOM_MASK    (sensorI2C_scl__0__HSIOM_MASK)
    #define sensorI2C_SCL_HSIOM_POS     (sensorI2C_scl__0__HSIOM_SHIFT)

    #define sensorI2C_SDA_HSIOM_REG     (*(reg32 *) sensorI2C_sda__0__HSIOM)
    #define sensorI2C_SDA_HSIOM_PTR     ( (reg32 *) sensorI2C_sda__0__HSIOM)
    #define sensorI2C_SDA_HSIOM_MASK    (sensorI2C_sda__0__HSIOM_MASK)
    #define sensorI2C_SDA_HSIOM_POS     (sensorI2C_sda__0__HSIOM_SHIFT)
#endif /* (sensorI2C_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define sensorI2C_HSIOM_DEF_SEL      (0x00u)
#define sensorI2C_HSIOM_GPIO_SEL     (0x00u)
#define sensorI2C_HSIOM_UART_SEL     (0x09u)
#define sensorI2C_HSIOM_I2C_SEL      (0x0Eu)
#define sensorI2C_HSIOM_SPI_SEL      (0x0Fu)

#define sensorI2C_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define sensorI2C_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define sensorI2C_MISO_SDA_TX_PIN_INDEX      (1u)
#define sensorI2C_SCLK_PIN_INDEX             (2u)
#define sensorI2C_SS0_PIN_INDEX              (3u)
#define sensorI2C_SS1_PIN_INDEX              (4u)
#define sensorI2C_SS2_PIN_INDEX              (5u)
#define sensorI2C_SS3_PIN_INDEX              (6u)

#define sensorI2C_MOSI_SCL_RX_PIN_MASK      ((uint32) 0x01u << sensorI2C_MOSI_SCL_RX_PIN_INDEX)
#define sensorI2C_MOSI_SCL_RX_WAKE_PIN_MASK ((uint32) 0x01u << sensorI2C_MOSI_SCL_RX_WAKE_PIN_INDEX)
#define sensorI2C_MISO_SDA_TX_PIN_MASK      ((uint32) 0x01u << sensorI2C_MISO_SDA_TX_PIN_INDEX)
#define sensorI2C_SCLK_PIN_MASK             ((uint32) 0x01u << sensorI2C_SCLK_PIN_INDEX)
#define sensorI2C_SS0_PIN_MASK              ((uint32) 0x01u << sensorI2C_SS0_PIN_INDEX)
#define sensorI2C_SS1_PIN_MASK              ((uint32) 0x01u << sensorI2C_SS1_PIN_INDEX)
#define sensorI2C_SS2_PIN_MASK              ((uint32) 0x01u << sensorI2C_SS2_PIN_INDEX)
#define sensorI2C_SS3_PIN_MASK              ((uint32) 0x01u << sensorI2C_SS3_PIN_INDEX)

#define sensorI2C_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define sensorI2C_PIN_DM_ALG_HIZ  (0u)
#define sensorI2C_PIN_DM_DIG_HIZ  (1u)
#define sensorI2C_PIN_DM_OD_LO    (4u)
#define sensorI2C_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Set bits-mask in register */
#define sensorI2C_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define sensorI2C_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define sensorI2C_SET_HSIOM_SEL(reg, mask, pos, sel) sensorI2C_SET_REGISTER_BITS(reg, mask, pos, sel)
#define sensorI2C_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        sensorI2C_SET_REGISTER_BITS(reg, mask, pos, intType)
#define sensorI2C_SET_INP_DIS(reg, mask, val) sensorI2C_SET_REGISTER_BIT(reg, mask, val)

/* sensorI2C_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  sensorI2C_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if(sensorI2C_I2C_PINS)
    #define sensorI2C_SET_I2C_SCL_DR(val) sensorI2C_scl_Write(val)

    #define sensorI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                          sensorI2C_SET_HSIOM_SEL(sensorI2C_SCL_HSIOM_REG,  \
                                                         sensorI2C_SCL_HSIOM_MASK, \
                                                         sensorI2C_SCL_HSIOM_POS,  \
                                                         (sel))
    #define sensorI2C_WAIT_SCL_SET_HIGH  (0u == sensorI2C_scl_Read())

/* Unconfigured SCB: scl signal */
#elif(sensorI2C_MOSI_SCL_RX_WAKE_PIN)
    #define sensorI2C_SET_I2C_SCL_DR(val) \
                            sensorI2C_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define sensorI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                    sensorI2C_SET_HSIOM_SEL(sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   sensorI2C_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

    #define sensorI2C_WAIT_SCL_SET_HIGH  (0u == sensorI2C_spi_mosi_i2c_scl_uart_rx_wake_Read())

#elif(sensorI2C_MOSI_SCL_RX_PIN)
    #define sensorI2C_SET_I2C_SCL_DR(val) \
                            sensorI2C_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define sensorI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                            sensorI2C_SET_HSIOM_SEL(sensorI2C_MOSI_SCL_RX_HSIOM_REG,  \
                                                           sensorI2C_MOSI_SCL_RX_HSIOM_MASK, \
                                                           sensorI2C_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))

    #define sensorI2C_WAIT_SCL_SET_HIGH  (0u == sensorI2C_spi_mosi_i2c_scl_uart_rx_Read())

#else
    #define sensorI2C_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define sensorI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define sensorI2C_WAIT_SCL_SET_HIGH  (0u)
#endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

/* SCB I2C: sda signal */
#if(sensorI2C_I2C_PINS)
    #define sensorI2C_WAIT_SDA_SET_HIGH  (0u == sensorI2C_sda_Read())

/* Unconfigured SCB: sda signal */
#elif(sensorI2C_MISO_SDA_TX_PIN)
    #define sensorI2C_WAIT_SDA_SET_HIGH  (0u == sensorI2C_spi_miso_i2c_sda_uart_tx_Read())

#else
    #define sensorI2C_WAIT_SDA_SET_HIGH  (0u)
#endif /* (sensorI2C_MOSI_SCL_RX_PIN) */

#endif /* (CY_SCB_PINS_sensorI2C_H) */


/* [] END OF FILE */
