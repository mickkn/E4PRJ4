.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu_trm.inc"

/* PWM_A */
.set PWM_A__0__DM__MASK, 0xE00
.set PWM_A__0__DM__SHIFT, 9
.set PWM_A__0__DR, CYREG_PRT1_DR
.set PWM_A__0__HSIOM, CYREG_HSIOM_PORT_SEL1
.set PWM_A__0__HSIOM_MASK, 0x0000F000
.set PWM_A__0__HSIOM_SHIFT, 12
.set PWM_A__0__INTCFG, CYREG_PRT1_INTCFG
.set PWM_A__0__INTSTAT, CYREG_PRT1_INTSTAT
.set PWM_A__0__MASK, 0x08
.set PWM_A__0__OUT_SEL, CYREG_UDB_PA1_CFG10
.set PWM_A__0__OUT_SEL_SHIFT, 6
.set PWM_A__0__OUT_SEL_VAL, 1
.set PWM_A__0__PA__CFG0, CYREG_UDB_PA1_CFG0
.set PWM_A__0__PA__CFG1, CYREG_UDB_PA1_CFG1
.set PWM_A__0__PA__CFG10, CYREG_UDB_PA1_CFG10
.set PWM_A__0__PA__CFG11, CYREG_UDB_PA1_CFG11
.set PWM_A__0__PA__CFG12, CYREG_UDB_PA1_CFG12
.set PWM_A__0__PA__CFG13, CYREG_UDB_PA1_CFG13
.set PWM_A__0__PA__CFG14, CYREG_UDB_PA1_CFG14
.set PWM_A__0__PA__CFG2, CYREG_UDB_PA1_CFG2
.set PWM_A__0__PA__CFG3, CYREG_UDB_PA1_CFG3
.set PWM_A__0__PA__CFG4, CYREG_UDB_PA1_CFG4
.set PWM_A__0__PA__CFG5, CYREG_UDB_PA1_CFG5
.set PWM_A__0__PA__CFG6, CYREG_UDB_PA1_CFG6
.set PWM_A__0__PA__CFG7, CYREG_UDB_PA1_CFG7
.set PWM_A__0__PA__CFG8, CYREG_UDB_PA1_CFG8
.set PWM_A__0__PA__CFG9, CYREG_UDB_PA1_CFG9
.set PWM_A__0__PC, CYREG_PRT1_PC
.set PWM_A__0__PC2, CYREG_PRT1_PC2
.set PWM_A__0__PORT, 1
.set PWM_A__0__PS, CYREG_PRT1_PS
.set PWM_A__0__SHIFT, 3
.set PWM_A__DR, CYREG_PRT1_DR
.set PWM_A__INTCFG, CYREG_PRT1_INTCFG
.set PWM_A__INTSTAT, CYREG_PRT1_INTSTAT
.set PWM_A__MASK, 0x08
.set PWM_A__PA__CFG0, CYREG_UDB_PA1_CFG0
.set PWM_A__PA__CFG1, CYREG_UDB_PA1_CFG1
.set PWM_A__PA__CFG10, CYREG_UDB_PA1_CFG10
.set PWM_A__PA__CFG11, CYREG_UDB_PA1_CFG11
.set PWM_A__PA__CFG12, CYREG_UDB_PA1_CFG12
.set PWM_A__PA__CFG13, CYREG_UDB_PA1_CFG13
.set PWM_A__PA__CFG14, CYREG_UDB_PA1_CFG14
.set PWM_A__PA__CFG2, CYREG_UDB_PA1_CFG2
.set PWM_A__PA__CFG3, CYREG_UDB_PA1_CFG3
.set PWM_A__PA__CFG4, CYREG_UDB_PA1_CFG4
.set PWM_A__PA__CFG5, CYREG_UDB_PA1_CFG5
.set PWM_A__PA__CFG6, CYREG_UDB_PA1_CFG6
.set PWM_A__PA__CFG7, CYREG_UDB_PA1_CFG7
.set PWM_A__PA__CFG8, CYREG_UDB_PA1_CFG8
.set PWM_A__PA__CFG9, CYREG_UDB_PA1_CFG9
.set PWM_A__PC, CYREG_PRT1_PC
.set PWM_A__PC2, CYREG_PRT1_PC2
.set PWM_A__PORT, 1
.set PWM_A__PS, CYREG_PRT1_PS
.set PWM_A__SHIFT, 3

/* PWM_B */
.set PWM_B__0__DM__MASK, 0x7000
.set PWM_B__0__DM__SHIFT, 12
.set PWM_B__0__DR, CYREG_PRT1_DR
.set PWM_B__0__HSIOM, CYREG_HSIOM_PORT_SEL1
.set PWM_B__0__HSIOM_MASK, 0x000F0000
.set PWM_B__0__HSIOM_SHIFT, 16
.set PWM_B__0__INTCFG, CYREG_PRT1_INTCFG
.set PWM_B__0__INTSTAT, CYREG_PRT1_INTSTAT
.set PWM_B__0__MASK, 0x10
.set PWM_B__0__OUT_SEL, CYREG_UDB_PA1_CFG10
.set PWM_B__0__OUT_SEL_SHIFT, 8
.set PWM_B__0__OUT_SEL_VAL, 2
.set PWM_B__0__PA__CFG0, CYREG_UDB_PA1_CFG0
.set PWM_B__0__PA__CFG1, CYREG_UDB_PA1_CFG1
.set PWM_B__0__PA__CFG10, CYREG_UDB_PA1_CFG10
.set PWM_B__0__PA__CFG11, CYREG_UDB_PA1_CFG11
.set PWM_B__0__PA__CFG12, CYREG_UDB_PA1_CFG12
.set PWM_B__0__PA__CFG13, CYREG_UDB_PA1_CFG13
.set PWM_B__0__PA__CFG14, CYREG_UDB_PA1_CFG14
.set PWM_B__0__PA__CFG2, CYREG_UDB_PA1_CFG2
.set PWM_B__0__PA__CFG3, CYREG_UDB_PA1_CFG3
.set PWM_B__0__PA__CFG4, CYREG_UDB_PA1_CFG4
.set PWM_B__0__PA__CFG5, CYREG_UDB_PA1_CFG5
.set PWM_B__0__PA__CFG6, CYREG_UDB_PA1_CFG6
.set PWM_B__0__PA__CFG7, CYREG_UDB_PA1_CFG7
.set PWM_B__0__PA__CFG8, CYREG_UDB_PA1_CFG8
.set PWM_B__0__PA__CFG9, CYREG_UDB_PA1_CFG9
.set PWM_B__0__PC, CYREG_PRT1_PC
.set PWM_B__0__PC2, CYREG_PRT1_PC2
.set PWM_B__0__PORT, 1
.set PWM_B__0__PS, CYREG_PRT1_PS
.set PWM_B__0__SHIFT, 4
.set PWM_B__DR, CYREG_PRT1_DR
.set PWM_B__INTCFG, CYREG_PRT1_INTCFG
.set PWM_B__INTSTAT, CYREG_PRT1_INTSTAT
.set PWM_B__MASK, 0x10
.set PWM_B__PA__CFG0, CYREG_UDB_PA1_CFG0
.set PWM_B__PA__CFG1, CYREG_UDB_PA1_CFG1
.set PWM_B__PA__CFG10, CYREG_UDB_PA1_CFG10
.set PWM_B__PA__CFG11, CYREG_UDB_PA1_CFG11
.set PWM_B__PA__CFG12, CYREG_UDB_PA1_CFG12
.set PWM_B__PA__CFG13, CYREG_UDB_PA1_CFG13
.set PWM_B__PA__CFG14, CYREG_UDB_PA1_CFG14
.set PWM_B__PA__CFG2, CYREG_UDB_PA1_CFG2
.set PWM_B__PA__CFG3, CYREG_UDB_PA1_CFG3
.set PWM_B__PA__CFG4, CYREG_UDB_PA1_CFG4
.set PWM_B__PA__CFG5, CYREG_UDB_PA1_CFG5
.set PWM_B__PA__CFG6, CYREG_UDB_PA1_CFG6
.set PWM_B__PA__CFG7, CYREG_UDB_PA1_CFG7
.set PWM_B__PA__CFG8, CYREG_UDB_PA1_CFG8
.set PWM_B__PA__CFG9, CYREG_UDB_PA1_CFG9
.set PWM_B__PC, CYREG_PRT1_PC
.set PWM_B__PC2, CYREG_PRT1_PC2
.set PWM_B__PORT, 1
.set PWM_B__PS, CYREG_PRT1_PS
.set PWM_B__SHIFT, 4

/* PWM_PWMUDB */
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG, CYREG_UDB_W16_ACTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG, CYREG_UDB_W16_CTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG, CYREG_UDB_W16_CTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG, CYREG_UDB_W16_CTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG, CYREG_UDB_W16_CTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG, CYREG_UDB_W16_MSK_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG, CYREG_UDB_W16_MSK_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG, CYREG_UDB_W16_MSK_02
.set PWM_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG, CYREG_UDB_W16_MSK_02
.set PWM_PWMUDB_genblk1_ctrlreg__7__MASK, 0x80
.set PWM_PWMUDB_genblk1_ctrlreg__7__POS, 7
.set PWM_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG, CYREG_UDB_W8_ACTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG, CYREG_UDB_W8_CTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG, CYREG_UDB_CAT16_CTL_ST_02
.set PWM_PWMUDB_genblk1_ctrlreg__COUNT_REG, CYREG_UDB_W8_CTL_02
.set PWM_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG, CYREG_UDB_CAT16_CTL_ST_02
.set PWM_PWMUDB_genblk1_ctrlreg__MASK, 0x80
.set PWM_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_02
.set PWM_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_02
.set PWM_PWMUDB_genblk1_ctrlreg__PERIOD_REG, CYREG_UDB_W8_MSK_02
.set PWM_PWMUDB_genblk7_dbctrlreg__0__MASK, 0x01
.set PWM_PWMUDB_genblk7_dbctrlreg__0__POS, 0
.set PWM_PWMUDB_genblk7_dbctrlreg__1__MASK, 0x02
.set PWM_PWMUDB_genblk7_dbctrlreg__1__POS, 1
.set PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_AUX_CTL_REG, CYREG_UDB_W8_ACTL_03
.set PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG, CYREG_UDB_W8_CTL_03
.set PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_ST_REG, CYREG_UDB_CAT16_CTL_ST_03
.set PWM_PWMUDB_genblk7_dbctrlreg__COUNT_REG, CYREG_UDB_W8_CTL_03
.set PWM_PWMUDB_genblk7_dbctrlreg__COUNT_ST_REG, CYREG_UDB_CAT16_CTL_ST_03
.set PWM_PWMUDB_genblk7_dbctrlreg__MASK, 0x03
.set PWM_PWMUDB_genblk7_dbctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set PWM_PWMUDB_genblk7_dbctrlreg__PER_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set PWM_PWMUDB_genblk7_dbctrlreg__PERIOD_REG, CYREG_UDB_W8_MSK_03
.set PWM_PWMUDB_genblk8_stsreg__0__MASK, 0x01
.set PWM_PWMUDB_genblk8_stsreg__0__POS, 0
.set PWM_PWMUDB_genblk8_stsreg__2__MASK, 0x04
.set PWM_PWMUDB_genblk8_stsreg__2__POS, 2
.set PWM_PWMUDB_genblk8_stsreg__3__MASK, 0x08
.set PWM_PWMUDB_genblk8_stsreg__3__POS, 3
.set PWM_PWMUDB_genblk8_stsreg__MASK, 0x0D
.set PWM_PWMUDB_genblk8_stsreg__MASK_REG, CYREG_UDB_W8_MSK_03
.set PWM_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set PWM_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set PWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG, CYREG_UDB_W8_ACTL_03
.set PWM_PWMUDB_genblk8_stsreg__STATUS_CNT_REG, CYREG_UDB_CAT16_CTL_ST_03
.set PWM_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG, CYREG_UDB_CAT16_CTL_ST_03
.set PWM_PWMUDB_genblk8_stsreg__STATUS_REG, CYREG_UDB_W8_ST_03
.set PWM_PWMUDB_sP8_pwmdp_u0__A0_A1_REG, CYREG_UDB_CAT16_A_03
.set PWM_PWMUDB_sP8_pwmdp_u0__A0_REG, CYREG_UDB_W8_A0_03
.set PWM_PWMUDB_sP8_pwmdp_u0__A1_REG, CYREG_UDB_W8_A1_03
.set PWM_PWMUDB_sP8_pwmdp_u0__D0_D1_REG, CYREG_UDB_CAT16_D_03
.set PWM_PWMUDB_sP8_pwmdp_u0__D0_REG, CYREG_UDB_W8_D0_03
.set PWM_PWMUDB_sP8_pwmdp_u0__D1_REG, CYREG_UDB_W8_D1_03
.set PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG, CYREG_UDB_W8_ACTL_03
.set PWM_PWMUDB_sP8_pwmdp_u0__F0_F1_REG, CYREG_UDB_CAT16_F_03
.set PWM_PWMUDB_sP8_pwmdp_u0__F0_REG, CYREG_UDB_W8_F0_03
.set PWM_PWMUDB_sP8_pwmdp_u0__F1_REG, CYREG_UDB_W8_F1_03
.set PWM_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set PWM_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03

/* UART_rx */
.set UART_rx__0__DM__MASK, 0x07
.set UART_rx__0__DM__SHIFT, 0
.set UART_rx__0__DR, CYREG_PRT4_DR
.set UART_rx__0__HSIOM, CYREG_HSIOM_PORT_SEL4
.set UART_rx__0__HSIOM_MASK, 0x0000000F
.set UART_rx__0__HSIOM_SHIFT, 0
.set UART_rx__0__INTCFG, CYREG_PRT4_INTCFG
.set UART_rx__0__INTSTAT, CYREG_PRT4_INTSTAT
.set UART_rx__0__MASK, 0x01
.set UART_rx__0__PC, CYREG_PRT4_PC
.set UART_rx__0__PC2, CYREG_PRT4_PC2
.set UART_rx__0__PORT, 4
.set UART_rx__0__PS, CYREG_PRT4_PS
.set UART_rx__0__SHIFT, 0
.set UART_rx__DR, CYREG_PRT4_DR
.set UART_rx__INTCFG, CYREG_PRT4_INTCFG
.set UART_rx__INTSTAT, CYREG_PRT4_INTSTAT
.set UART_rx__MASK, 0x01
.set UART_rx__PC, CYREG_PRT4_PC
.set UART_rx__PC2, CYREG_PRT4_PC2
.set UART_rx__PORT, 4
.set UART_rx__PS, CYREG_PRT4_PS
.set UART_rx__SHIFT, 0

/* UART_SCB */
.set UART_SCB__BIST_CONTROL, CYREG_SCB0_BIST_CONTROL
.set UART_SCB__BIST_DATA, CYREG_SCB0_BIST_DATA
.set UART_SCB__CTRL, CYREG_SCB0_CTRL
.set UART_SCB__EZ_DATA00, CYREG_SCB0_EZ_DATA00
.set UART_SCB__EZ_DATA01, CYREG_SCB0_EZ_DATA01
.set UART_SCB__EZ_DATA02, CYREG_SCB0_EZ_DATA02
.set UART_SCB__EZ_DATA03, CYREG_SCB0_EZ_DATA03
.set UART_SCB__EZ_DATA04, CYREG_SCB0_EZ_DATA04
.set UART_SCB__EZ_DATA05, CYREG_SCB0_EZ_DATA05
.set UART_SCB__EZ_DATA06, CYREG_SCB0_EZ_DATA06
.set UART_SCB__EZ_DATA07, CYREG_SCB0_EZ_DATA07
.set UART_SCB__EZ_DATA08, CYREG_SCB0_EZ_DATA08
.set UART_SCB__EZ_DATA09, CYREG_SCB0_EZ_DATA09
.set UART_SCB__EZ_DATA10, CYREG_SCB0_EZ_DATA10
.set UART_SCB__EZ_DATA11, CYREG_SCB0_EZ_DATA11
.set UART_SCB__EZ_DATA12, CYREG_SCB0_EZ_DATA12
.set UART_SCB__EZ_DATA13, CYREG_SCB0_EZ_DATA13
.set UART_SCB__EZ_DATA14, CYREG_SCB0_EZ_DATA14
.set UART_SCB__EZ_DATA15, CYREG_SCB0_EZ_DATA15
.set UART_SCB__EZ_DATA16, CYREG_SCB0_EZ_DATA16
.set UART_SCB__EZ_DATA17, CYREG_SCB0_EZ_DATA17
.set UART_SCB__EZ_DATA18, CYREG_SCB0_EZ_DATA18
.set UART_SCB__EZ_DATA19, CYREG_SCB0_EZ_DATA19
.set UART_SCB__EZ_DATA20, CYREG_SCB0_EZ_DATA20
.set UART_SCB__EZ_DATA21, CYREG_SCB0_EZ_DATA21
.set UART_SCB__EZ_DATA22, CYREG_SCB0_EZ_DATA22
.set UART_SCB__EZ_DATA23, CYREG_SCB0_EZ_DATA23
.set UART_SCB__EZ_DATA24, CYREG_SCB0_EZ_DATA24
.set UART_SCB__EZ_DATA25, CYREG_SCB0_EZ_DATA25
.set UART_SCB__EZ_DATA26, CYREG_SCB0_EZ_DATA26
.set UART_SCB__EZ_DATA27, CYREG_SCB0_EZ_DATA27
.set UART_SCB__EZ_DATA28, CYREG_SCB0_EZ_DATA28
.set UART_SCB__EZ_DATA29, CYREG_SCB0_EZ_DATA29
.set UART_SCB__EZ_DATA30, CYREG_SCB0_EZ_DATA30
.set UART_SCB__EZ_DATA31, CYREG_SCB0_EZ_DATA31
.set UART_SCB__I2C_CFG, CYREG_SCB0_I2C_CFG
.set UART_SCB__I2C_CTRL, CYREG_SCB0_I2C_CTRL
.set UART_SCB__I2C_M_CMD, CYREG_SCB0_I2C_M_CMD
.set UART_SCB__I2C_S_CMD, CYREG_SCB0_I2C_S_CMD
.set UART_SCB__I2C_STATUS, CYREG_SCB0_I2C_STATUS
.set UART_SCB__INTR_CAUSE, CYREG_SCB0_INTR_CAUSE
.set UART_SCB__INTR_I2C_EC, CYREG_SCB0_INTR_I2C_EC
.set UART_SCB__INTR_I2C_EC_MASK, CYREG_SCB0_INTR_I2C_EC_MASK
.set UART_SCB__INTR_I2C_EC_MASKED, CYREG_SCB0_INTR_I2C_EC_MASKED
.set UART_SCB__INTR_M, CYREG_SCB0_INTR_M
.set UART_SCB__INTR_M_MASK, CYREG_SCB0_INTR_M_MASK
.set UART_SCB__INTR_M_MASKED, CYREG_SCB0_INTR_M_MASKED
.set UART_SCB__INTR_M_SET, CYREG_SCB0_INTR_M_SET
.set UART_SCB__INTR_RX, CYREG_SCB0_INTR_RX
.set UART_SCB__INTR_RX_MASK, CYREG_SCB0_INTR_RX_MASK
.set UART_SCB__INTR_RX_MASKED, CYREG_SCB0_INTR_RX_MASKED
.set UART_SCB__INTR_RX_SET, CYREG_SCB0_INTR_RX_SET
.set UART_SCB__INTR_S, CYREG_SCB0_INTR_S
.set UART_SCB__INTR_S_MASK, CYREG_SCB0_INTR_S_MASK
.set UART_SCB__INTR_S_MASKED, CYREG_SCB0_INTR_S_MASKED
.set UART_SCB__INTR_S_SET, CYREG_SCB0_INTR_S_SET
.set UART_SCB__INTR_SPI_EC, CYREG_SCB0_INTR_SPI_EC
.set UART_SCB__INTR_SPI_EC_MASK, CYREG_SCB0_INTR_SPI_EC_MASK
.set UART_SCB__INTR_SPI_EC_MASKED, CYREG_SCB0_INTR_SPI_EC_MASKED
.set UART_SCB__INTR_TX, CYREG_SCB0_INTR_TX
.set UART_SCB__INTR_TX_MASK, CYREG_SCB0_INTR_TX_MASK
.set UART_SCB__INTR_TX_MASKED, CYREG_SCB0_INTR_TX_MASKED
.set UART_SCB__INTR_TX_SET, CYREG_SCB0_INTR_TX_SET
.set UART_SCB__RX_CTRL, CYREG_SCB0_RX_CTRL
.set UART_SCB__RX_FIFO_CTRL, CYREG_SCB0_RX_FIFO_CTRL
.set UART_SCB__RX_FIFO_RD, CYREG_SCB0_RX_FIFO_RD
.set UART_SCB__RX_FIFO_RD_SILENT, CYREG_SCB0_RX_FIFO_RD_SILENT
.set UART_SCB__RX_FIFO_STATUS, CYREG_SCB0_RX_FIFO_STATUS
.set UART_SCB__RX_MATCH, CYREG_SCB0_RX_MATCH
.set UART_SCB__SPI_CTRL, CYREG_SCB0_SPI_CTRL
.set UART_SCB__SPI_STATUS, CYREG_SCB0_SPI_STATUS
.set UART_SCB__SS0_POSISTION, 0
.set UART_SCB__SS1_POSISTION, 1
.set UART_SCB__SS2_POSISTION, 2
.set UART_SCB__SS3_POSISTION, 3
.set UART_SCB__STATUS, CYREG_SCB0_STATUS
.set UART_SCB__TX_CTRL, CYREG_SCB0_TX_CTRL
.set UART_SCB__TX_FIFO_CTRL, CYREG_SCB0_TX_FIFO_CTRL
.set UART_SCB__TX_FIFO_STATUS, CYREG_SCB0_TX_FIFO_STATUS
.set UART_SCB__TX_FIFO_WR, CYREG_SCB0_TX_FIFO_WR
.set UART_SCB__UART_CTRL, CYREG_SCB0_UART_CTRL
.set UART_SCB__UART_RX_CTRL, CYREG_SCB0_UART_RX_CTRL
.set UART_SCB__UART_RX_STATUS, CYREG_SCB0_UART_RX_STATUS
.set UART_SCB__UART_TX_CTRL, CYREG_SCB0_UART_TX_CTRL

/* UART_SCBCLK */
.set UART_SCBCLK__DIVIDER_MASK, 0x0000FFFF
.set UART_SCBCLK__ENABLE, CYREG_CLK_DIVIDER_B00
.set UART_SCBCLK__ENABLE_MASK, 0x80000000
.set UART_SCBCLK__MASK, 0x80000000
.set UART_SCBCLK__REGISTER, CYREG_CLK_DIVIDER_B00

/* UART_tx */
.set UART_tx__0__DM__MASK, 0x38
.set UART_tx__0__DM__SHIFT, 3
.set UART_tx__0__DR, CYREG_PRT4_DR
.set UART_tx__0__HSIOM, CYREG_HSIOM_PORT_SEL4
.set UART_tx__0__HSIOM_MASK, 0x000000F0
.set UART_tx__0__HSIOM_SHIFT, 4
.set UART_tx__0__INTCFG, CYREG_PRT4_INTCFG
.set UART_tx__0__INTSTAT, CYREG_PRT4_INTSTAT
.set UART_tx__0__MASK, 0x02
.set UART_tx__0__PC, CYREG_PRT4_PC
.set UART_tx__0__PC2, CYREG_PRT4_PC2
.set UART_tx__0__PORT, 4
.set UART_tx__0__PS, CYREG_PRT4_PS
.set UART_tx__0__SHIFT, 1
.set UART_tx__DR, CYREG_PRT4_DR
.set UART_tx__INTCFG, CYREG_PRT4_INTCFG
.set UART_tx__INTSTAT, CYREG_PRT4_INTSTAT
.set UART_tx__MASK, 0x02
.set UART_tx__PC, CYREG_PRT4_PC
.set UART_tx__PC2, CYREG_PRT4_PC2
.set UART_tx__PORT, 4
.set UART_tx__PS, CYREG_PRT4_PS
.set UART_tx__SHIFT, 1

/* Pin_1 */
.set Pin_1__0__DM__MASK, 0x1C0
.set Pin_1__0__DM__SHIFT, 6
.set Pin_1__0__DR, CYREG_PRT0_DR
.set Pin_1__0__HSIOM, CYREG_HSIOM_PORT_SEL0
.set Pin_1__0__HSIOM_MASK, 0x00000F00
.set Pin_1__0__HSIOM_SHIFT, 8
.set Pin_1__0__INTCFG, CYREG_PRT0_INTCFG
.set Pin_1__0__INTSTAT, CYREG_PRT0_INTSTAT
.set Pin_1__0__MASK, 0x04
.set Pin_1__0__PA__CFG0, CYREG_UDB_PA0_CFG0
.set Pin_1__0__PA__CFG1, CYREG_UDB_PA0_CFG1
.set Pin_1__0__PA__CFG10, CYREG_UDB_PA0_CFG10
.set Pin_1__0__PA__CFG11, CYREG_UDB_PA0_CFG11
.set Pin_1__0__PA__CFG12, CYREG_UDB_PA0_CFG12
.set Pin_1__0__PA__CFG13, CYREG_UDB_PA0_CFG13
.set Pin_1__0__PA__CFG14, CYREG_UDB_PA0_CFG14
.set Pin_1__0__PA__CFG2, CYREG_UDB_PA0_CFG2
.set Pin_1__0__PA__CFG3, CYREG_UDB_PA0_CFG3
.set Pin_1__0__PA__CFG4, CYREG_UDB_PA0_CFG4
.set Pin_1__0__PA__CFG5, CYREG_UDB_PA0_CFG5
.set Pin_1__0__PA__CFG6, CYREG_UDB_PA0_CFG6
.set Pin_1__0__PA__CFG7, CYREG_UDB_PA0_CFG7
.set Pin_1__0__PA__CFG8, CYREG_UDB_PA0_CFG8
.set Pin_1__0__PA__CFG9, CYREG_UDB_PA0_CFG9
.set Pin_1__0__PC, CYREG_PRT0_PC
.set Pin_1__0__PC2, CYREG_PRT0_PC2
.set Pin_1__0__PORT, 0
.set Pin_1__0__PS, CYREG_PRT0_PS
.set Pin_1__0__SHIFT, 2
.set Pin_1__DR, CYREG_PRT0_DR
.set Pin_1__INTCFG, CYREG_PRT0_INTCFG
.set Pin_1__INTSTAT, CYREG_PRT0_INTSTAT
.set Pin_1__MASK, 0x04
.set Pin_1__PA__CFG0, CYREG_UDB_PA0_CFG0
.set Pin_1__PA__CFG1, CYREG_UDB_PA0_CFG1
.set Pin_1__PA__CFG10, CYREG_UDB_PA0_CFG10
.set Pin_1__PA__CFG11, CYREG_UDB_PA0_CFG11
.set Pin_1__PA__CFG12, CYREG_UDB_PA0_CFG12
.set Pin_1__PA__CFG13, CYREG_UDB_PA0_CFG13
.set Pin_1__PA__CFG14, CYREG_UDB_PA0_CFG14
.set Pin_1__PA__CFG2, CYREG_UDB_PA0_CFG2
.set Pin_1__PA__CFG3, CYREG_UDB_PA0_CFG3
.set Pin_1__PA__CFG4, CYREG_UDB_PA0_CFG4
.set Pin_1__PA__CFG5, CYREG_UDB_PA0_CFG5
.set Pin_1__PA__CFG6, CYREG_UDB_PA0_CFG6
.set Pin_1__PA__CFG7, CYREG_UDB_PA0_CFG7
.set Pin_1__PA__CFG8, CYREG_UDB_PA0_CFG8
.set Pin_1__PA__CFG9, CYREG_UDB_PA0_CFG9
.set Pin_1__PC, CYREG_PRT0_PC
.set Pin_1__PC2, CYREG_PRT0_PC2
.set Pin_1__PORT, 0
.set Pin_1__PS, CYREG_PRT0_PS
.set Pin_1__SHIFT, 2

/* isr_1 */
.set isr_1__INTC_CLR_EN_REG, CYREG_CM0_ICER
.set isr_1__INTC_CLR_PD_REG, CYREG_CM0_ICPR
.set isr_1__INTC_MASK, 0x01
.set isr_1__INTC_NUMBER, 0
.set isr_1__INTC_PRIOR_MASK, 0xC0
.set isr_1__INTC_PRIOR_NUM, 3
.set isr_1__INTC_PRIOR_REG, CYREG_CM0_IPR0
.set isr_1__INTC_SET_EN_REG, CYREG_CM0_ISER
.set isr_1__INTC_SET_PD_REG, CYREG_CM0_ISPR

/* Clock_1 */
.set Clock_1__DIVIDER_MASK, 0x0000FFFF
.set Clock_1__ENABLE, CYREG_CLK_DIVIDER_A00
.set Clock_1__ENABLE_MASK, 0x80000000
.set Clock_1__MASK, 0x80000000
.set Clock_1__REGISTER, CYREG_CLK_DIVIDER_A00

/* ISR_Pin */
.set ISR_Pin__0__DM__MASK, 0x07
.set ISR_Pin__0__DM__SHIFT, 0
.set ISR_Pin__0__DR, CYREG_PRT0_DR
.set ISR_Pin__0__HSIOM, CYREG_HSIOM_PORT_SEL0
.set ISR_Pin__0__HSIOM_MASK, 0x0000000F
.set ISR_Pin__0__HSIOM_SHIFT, 0
.set ISR_Pin__0__INTCFG, CYREG_PRT0_INTCFG
.set ISR_Pin__0__INTSTAT, CYREG_PRT0_INTSTAT
.set ISR_Pin__0__MASK, 0x01
.set ISR_Pin__0__PA__CFG0, CYREG_UDB_PA0_CFG0
.set ISR_Pin__0__PA__CFG1, CYREG_UDB_PA0_CFG1
.set ISR_Pin__0__PA__CFG10, CYREG_UDB_PA0_CFG10
.set ISR_Pin__0__PA__CFG11, CYREG_UDB_PA0_CFG11
.set ISR_Pin__0__PA__CFG12, CYREG_UDB_PA0_CFG12
.set ISR_Pin__0__PA__CFG13, CYREG_UDB_PA0_CFG13
.set ISR_Pin__0__PA__CFG14, CYREG_UDB_PA0_CFG14
.set ISR_Pin__0__PA__CFG2, CYREG_UDB_PA0_CFG2
.set ISR_Pin__0__PA__CFG3, CYREG_UDB_PA0_CFG3
.set ISR_Pin__0__PA__CFG4, CYREG_UDB_PA0_CFG4
.set ISR_Pin__0__PA__CFG5, CYREG_UDB_PA0_CFG5
.set ISR_Pin__0__PA__CFG6, CYREG_UDB_PA0_CFG6
.set ISR_Pin__0__PA__CFG7, CYREG_UDB_PA0_CFG7
.set ISR_Pin__0__PA__CFG8, CYREG_UDB_PA0_CFG8
.set ISR_Pin__0__PA__CFG9, CYREG_UDB_PA0_CFG9
.set ISR_Pin__0__PC, CYREG_PRT0_PC
.set ISR_Pin__0__PC2, CYREG_PRT0_PC2
.set ISR_Pin__0__PORT, 0
.set ISR_Pin__0__PS, CYREG_PRT0_PS
.set ISR_Pin__0__SHIFT, 0
.set ISR_Pin__DR, CYREG_PRT0_DR
.set ISR_Pin__INTCFG, CYREG_PRT0_INTCFG
.set ISR_Pin__INTSTAT, CYREG_PRT0_INTSTAT
.set ISR_Pin__MASK, 0x01
.set ISR_Pin__PA__CFG0, CYREG_UDB_PA0_CFG0
.set ISR_Pin__PA__CFG1, CYREG_UDB_PA0_CFG1
.set ISR_Pin__PA__CFG10, CYREG_UDB_PA0_CFG10
.set ISR_Pin__PA__CFG11, CYREG_UDB_PA0_CFG11
.set ISR_Pin__PA__CFG12, CYREG_UDB_PA0_CFG12
.set ISR_Pin__PA__CFG13, CYREG_UDB_PA0_CFG13
.set ISR_Pin__PA__CFG14, CYREG_UDB_PA0_CFG14
.set ISR_Pin__PA__CFG2, CYREG_UDB_PA0_CFG2
.set ISR_Pin__PA__CFG3, CYREG_UDB_PA0_CFG3
.set ISR_Pin__PA__CFG4, CYREG_UDB_PA0_CFG4
.set ISR_Pin__PA__CFG5, CYREG_UDB_PA0_CFG5
.set ISR_Pin__PA__CFG6, CYREG_UDB_PA0_CFG6
.set ISR_Pin__PA__CFG7, CYREG_UDB_PA0_CFG7
.set ISR_Pin__PA__CFG8, CYREG_UDB_PA0_CFG8
.set ISR_Pin__PA__CFG9, CYREG_UDB_PA0_CFG9
.set ISR_Pin__PC, CYREG_PRT0_PC
.set ISR_Pin__PC2, CYREG_PRT0_PC2
.set ISR_Pin__PORT, 0
.set ISR_Pin__PS, CYREG_PRT0_PS
.set ISR_Pin__SHIFT, 0

/* timer_clock */
.set timer_clock__DIVIDER_MASK, 0x0000FFFF
.set timer_clock__ENABLE, CYREG_CLK_DIVIDER_C00
.set timer_clock__ENABLE_MASK, 0x80000000
.set timer_clock__MASK, 0x80000000
.set timer_clock__REGISTER, CYREG_CLK_DIVIDER_C00

/* Timer_TimerUDB */
.set Timer_TimerUDB_rstSts_stsreg__0__MASK, 0x01
.set Timer_TimerUDB_rstSts_stsreg__0__POS, 0
.set Timer_TimerUDB_rstSts_stsreg__16BIT_STATUS_AUX_CTL_REG, CYREG_UDB_W16_ACTL_01
.set Timer_TimerUDB_rstSts_stsreg__16BIT_STATUS_REG, CYREG_UDB_W16_ST_01
.set Timer_TimerUDB_rstSts_stsreg__2__MASK, 0x04
.set Timer_TimerUDB_rstSts_stsreg__2__POS, 2
.set Timer_TimerUDB_rstSts_stsreg__3__MASK, 0x08
.set Timer_TimerUDB_rstSts_stsreg__3__POS, 3
.set Timer_TimerUDB_rstSts_stsreg__MASK, 0x0D
.set Timer_TimerUDB_rstSts_stsreg__MASK_REG, CYREG_UDB_W8_MSK_01
.set Timer_TimerUDB_rstSts_stsreg__MASK_ST_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_01
.set Timer_TimerUDB_rstSts_stsreg__PER_ST_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_01
.set Timer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG, CYREG_UDB_W8_ACTL_01
.set Timer_TimerUDB_rstSts_stsreg__STATUS_CNT_REG, CYREG_UDB_CAT16_CTL_ST_01
.set Timer_TimerUDB_rstSts_stsreg__STATUS_CONTROL_REG, CYREG_UDB_CAT16_CTL_ST_01
.set Timer_TimerUDB_rstSts_stsreg__STATUS_REG, CYREG_UDB_W8_ST_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG, CYREG_UDB_W16_ACTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG, CYREG_UDB_W16_CTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG, CYREG_UDB_W16_CTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG, CYREG_UDB_W16_CTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG, CYREG_UDB_W16_CTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_MASK_REG, CYREG_UDB_W16_MSK_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG, CYREG_UDB_W16_MSK_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG, CYREG_UDB_W16_MSK_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG, CYREG_UDB_W16_MSK_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__7__MASK, 0x80
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__7__POS, 7
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_AUX_CTL_REG, CYREG_UDB_W8_ACTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG, CYREG_UDB_W8_CTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_ST_REG, CYREG_UDB_CAT16_CTL_ST_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_REG, CYREG_UDB_W8_CTL_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_ST_REG, CYREG_UDB_CAT16_CTL_ST_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__MASK, 0x80
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_01
.set Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__PERIOD_REG, CYREG_UDB_W8_MSK_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG, CYREG_UDB_W16_A0_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_A1_REG, CYREG_UDB_W16_A1_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG, CYREG_UDB_W16_D0_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_D1_REG, CYREG_UDB_W16_D1_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_DP_AUX_CTL_REG, CYREG_UDB_W16_ACTL_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG, CYREG_UDB_W16_F0_01
.set Timer_TimerUDB_sT8_timerdp_u0__16BIT_F1_REG, CYREG_UDB_W16_F1_01
.set Timer_TimerUDB_sT8_timerdp_u0__A0_A1_REG, CYREG_UDB_CAT16_A_01
.set Timer_TimerUDB_sT8_timerdp_u0__A0_REG, CYREG_UDB_W8_A0_01
.set Timer_TimerUDB_sT8_timerdp_u0__A1_REG, CYREG_UDB_W8_A1_01
.set Timer_TimerUDB_sT8_timerdp_u0__D0_D1_REG, CYREG_UDB_CAT16_D_01
.set Timer_TimerUDB_sT8_timerdp_u0__D0_REG, CYREG_UDB_W8_D0_01
.set Timer_TimerUDB_sT8_timerdp_u0__D1_REG, CYREG_UDB_W8_D1_01
.set Timer_TimerUDB_sT8_timerdp_u0__DP_AUX_CTL_REG, CYREG_UDB_W8_ACTL_01
.set Timer_TimerUDB_sT8_timerdp_u0__F0_F1_REG, CYREG_UDB_CAT16_F_01
.set Timer_TimerUDB_sT8_timerdp_u0__F0_REG, CYREG_UDB_W8_F0_01
.set Timer_TimerUDB_sT8_timerdp_u0__F1_REG, CYREG_UDB_W8_F1_01
.set Timer_TimerUDB_sT8_timerdp_u0__MSK_DP_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_01
.set Timer_TimerUDB_sT8_timerdp_u0__PER_DP_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_01

/* Miscellaneous */
.set CYDEV_BCLK__HFCLK__HZ, 48000000
.set CYDEV_BCLK__HFCLK__KHZ, 48000
.set CYDEV_BCLK__HFCLK__MHZ, 48
.set CYDEV_BCLK__SYSCLK__HZ, 48000000
.set CYDEV_BCLK__SYSCLK__KHZ, 48000
.set CYDEV_BCLK__SYSCLK__MHZ, 48
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PANTHER, 6
.set CYDEV_CHIP_DIE_PSOC4A, 3
.set CYDEV_CHIP_DIE_PSOC5LP, 5
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC4
.set CYDEV_CHIP_JTAG_ID, 0x04C81193
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 3
.set CYDEV_CHIP_MEMBER_4D, 2
.set CYDEV_CHIP_MEMBER_4F, 4
.set CYDEV_CHIP_MEMBER_5A, 6
.set CYDEV_CHIP_MEMBER_5B, 5
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_4A
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PANTHER_ES0, 0
.set CYDEV_CHIP_REV_PANTHER_ES1, 1
.set CYDEV_CHIP_REV_PANTHER_PRODUCTION, 1
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_4A_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_READ_ACCELERATOR, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_PROTECT_KILL, 4
.set CYDEV_DEBUG_PROTECT_OPEN, 1
.set CYDEV_DEBUG_PROTECT, CYDEV_DEBUG_PROTECT_OPEN
.set CYDEV_DEBUG_PROTECT_PROTECTED, 2
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_HEAP_SIZE, 0x80
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_STACK_SIZE, 0x0400
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 1
.set CYDEV_VDDA_MV, 3300
.set CYDEV_VDDD_MV, 3300
.set CYIPBLOCK_M0S8_CTBM_VERSION, 0
.set CYIPBLOCK_m0s8cpuss_VERSION, 0
.set CYIPBLOCK_m0s8csd_VERSION, 0
.set CYIPBLOCK_m0s8gpio2_VERSION, 0
.set CYIPBLOCK_m0s8hsiom4a_VERSION, 0
.set CYIPBLOCK_m0s8lcd_VERSION, 0
.set CYIPBLOCK_m0s8lpcomp_VERSION, 0
.set CYIPBLOCK_m0s8pclk_VERSION, 0
.set CYIPBLOCK_m0s8sar_VERSION, 0
.set CYIPBLOCK_m0s8scb_VERSION, 0
.set CYIPBLOCK_m0s8srssv2_VERSION, 1
.set CYIPBLOCK_m0s8tcpwm_VERSION, 0
.set CYIPBLOCK_m0s8udbif_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 2
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif