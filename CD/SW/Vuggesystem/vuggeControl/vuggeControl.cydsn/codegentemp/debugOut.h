/*******************************************************************************
* File Name: debugOut.h
* Version 2.40
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_debugOut_H)
#define CY_UART_debugOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define debugOut_RX_ENABLED                     (0u)
#define debugOut_TX_ENABLED                     (1u)
#define debugOut_HD_ENABLED                     (0u)
#define debugOut_RX_INTERRUPT_ENABLED           (0u)
#define debugOut_TX_INTERRUPT_ENABLED           (0u)
#define debugOut_INTERNAL_CLOCK_USED            (1u)
#define debugOut_RXHW_ADDRESS_ENABLED           (0u)
#define debugOut_OVER_SAMPLE_COUNT              (8u)
#define debugOut_PARITY_TYPE                    (0u)
#define debugOut_PARITY_TYPE_SW                 (0u)
#define debugOut_BREAK_DETECT                   (0u)
#define debugOut_BREAK_BITS_TX                  (13u)
#define debugOut_BREAK_BITS_RX                  (13u)
#define debugOut_TXCLKGEN_DP                    (1u)
#define debugOut_USE23POLLING                   (1u)
#define debugOut_FLOW_CONTROL                   (0u)
#define debugOut_CLK_FREQ                       (0u)
#define debugOut_TX_BUFFER_SIZE                 (4u)
#define debugOut_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define debugOut_CONTROL_REG_REMOVED            (0u)
#else
    #define debugOut_CONTROL_REG_REMOVED            (1u)
#endif /* End debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct debugOut_backupStruct_
{
    uint8 enableState;

    #if(debugOut_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End debugOut_CONTROL_REG_REMOVED */

} debugOut_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void debugOut_Start(void) ;
void debugOut_Stop(void) ;
uint8 debugOut_ReadControlRegister(void) ;
void debugOut_WriteControlRegister(uint8 control) ;

void debugOut_Init(void) ;
void debugOut_Enable(void) ;
void debugOut_SaveConfig(void) ;
void debugOut_RestoreConfig(void) ;
void debugOut_Sleep(void) ;
void debugOut_Wakeup(void) ;

/* Only if RX is enabled */
#if( (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) )

    #if (debugOut_RX_INTERRUPT_ENABLED)
        #define debugOut_EnableRxInt()  CyIntEnable (debugOut_RX_VECT_NUM)
        #define debugOut_DisableRxInt() CyIntDisable(debugOut_RX_VECT_NUM)
        CY_ISR_PROTO(debugOut_RXISR);
    #endif /* debugOut_RX_INTERRUPT_ENABLED */

    void debugOut_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void debugOut_SetRxAddress1(uint8 address) ;
    void debugOut_SetRxAddress2(uint8 address) ;

    void  debugOut_SetRxInterruptMode(uint8 intSrc) ;
    uint8 debugOut_ReadRxData(void) ;
    uint8 debugOut_ReadRxStatus(void) ;
    uint8 debugOut_GetChar(void) ;
    uint16 debugOut_GetByte(void) ;
    uint8 debugOut_GetRxBufferSize(void)
                                                            ;
    void debugOut_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define debugOut_GetRxInterruptSource   debugOut_ReadRxStatus

#endif /* End (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) */

/* Only if TX is enabled */
#if(debugOut_TX_ENABLED || debugOut_HD_ENABLED)

    #if(debugOut_TX_INTERRUPT_ENABLED)
        #define debugOut_EnableTxInt()  CyIntEnable (debugOut_TX_VECT_NUM)
        #define debugOut_DisableTxInt() CyIntDisable(debugOut_TX_VECT_NUM)
        #define debugOut_SetPendingTxInt() CyIntSetPending(debugOut_TX_VECT_NUM)
        #define debugOut_ClearPendingTxInt() CyIntClearPending(debugOut_TX_VECT_NUM)
        CY_ISR_PROTO(debugOut_TXISR);
    #endif /* debugOut_TX_INTERRUPT_ENABLED */

    void debugOut_SetTxInterruptMode(uint8 intSrc) ;
    void debugOut_WriteTxData(uint8 txDataByte) ;
    uint8 debugOut_ReadTxStatus(void) ;
    void debugOut_PutChar(uint8 txDataByte) ;
    void debugOut_PutString(const char8 string[]) ;
    void debugOut_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void debugOut_PutCRLF(uint8 txDataByte) ;
    void debugOut_ClearTxBuffer(void) ;
    void debugOut_SetTxAddressMode(uint8 addressMode) ;
    void debugOut_SendBreak(uint8 retMode) ;
    uint8 debugOut_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define debugOut_PutStringConst         debugOut_PutString
    #define debugOut_PutArrayConst          debugOut_PutArray
    #define debugOut_GetTxInterruptSource   debugOut_ReadTxStatus

#endif /* End debugOut_TX_ENABLED || debugOut_HD_ENABLED */

#if(debugOut_HD_ENABLED)
    void debugOut_LoadRxConfig(void) ;
    void debugOut_LoadTxConfig(void) ;
#endif /* End debugOut_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_debugOut) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    debugOut_CyBtldrCommStart(void) CYSMALL ;
    void    debugOut_CyBtldrCommStop(void) CYSMALL ;
    void    debugOut_CyBtldrCommReset(void) CYSMALL ;
    cystatus debugOut_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus debugOut_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_debugOut)
        #define CyBtldrCommStart    debugOut_CyBtldrCommStart
        #define CyBtldrCommStop     debugOut_CyBtldrCommStop
        #define CyBtldrCommReset    debugOut_CyBtldrCommReset
        #define CyBtldrCommWrite    debugOut_CyBtldrCommWrite
        #define CyBtldrCommRead     debugOut_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_debugOut) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define debugOut_BYTE2BYTE_TIME_OUT (25u)
    #define debugOut_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define debugOut_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define debugOut_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define debugOut_SET_SPACE      (0x00u)
#define debugOut_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (debugOut_TX_ENABLED) || (debugOut_HD_ENABLED) )
    #if(debugOut_TX_INTERRUPT_ENABLED)
        #define debugOut_TX_VECT_NUM            (uint8)debugOut_TXInternalInterrupt__INTC_NUMBER
        #define debugOut_TX_PRIOR_NUM           (uint8)debugOut_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* debugOut_TX_INTERRUPT_ENABLED */

    #define debugOut_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define debugOut_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define debugOut_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(debugOut_TX_ENABLED)
        #define debugOut_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (debugOut_HD_ENABLED) */
        #define debugOut_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (debugOut_TX_ENABLED) */

    #define debugOut_TX_STS_COMPLETE            (uint8)(0x01u << debugOut_TX_STS_COMPLETE_SHIFT)
    #define debugOut_TX_STS_FIFO_EMPTY          (uint8)(0x01u << debugOut_TX_STS_FIFO_EMPTY_SHIFT)
    #define debugOut_TX_STS_FIFO_FULL           (uint8)(0x01u << debugOut_TX_STS_FIFO_FULL_SHIFT)
    #define debugOut_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << debugOut_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (debugOut_TX_ENABLED) || (debugOut_HD_ENABLED)*/

#if( (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) )
    #if(debugOut_RX_INTERRUPT_ENABLED)
        #define debugOut_RX_VECT_NUM            (uint8)debugOut_RXInternalInterrupt__INTC_NUMBER
        #define debugOut_RX_PRIOR_NUM           (uint8)debugOut_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* debugOut_RX_INTERRUPT_ENABLED */
    #define debugOut_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define debugOut_RX_STS_BREAK_SHIFT             (0x01u)
    #define debugOut_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define debugOut_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define debugOut_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define debugOut_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define debugOut_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define debugOut_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define debugOut_RX_STS_MRKSPC           (uint8)(0x01u << debugOut_RX_STS_MRKSPC_SHIFT)
    #define debugOut_RX_STS_BREAK            (uint8)(0x01u << debugOut_RX_STS_BREAK_SHIFT)
    #define debugOut_RX_STS_PAR_ERROR        (uint8)(0x01u << debugOut_RX_STS_PAR_ERROR_SHIFT)
    #define debugOut_RX_STS_STOP_ERROR       (uint8)(0x01u << debugOut_RX_STS_STOP_ERROR_SHIFT)
    #define debugOut_RX_STS_OVERRUN          (uint8)(0x01u << debugOut_RX_STS_OVERRUN_SHIFT)
    #define debugOut_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << debugOut_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define debugOut_RX_STS_ADDR_MATCH       (uint8)(0x01u << debugOut_RX_STS_ADDR_MATCH_SHIFT)
    #define debugOut_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << debugOut_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define debugOut_RX_HW_MASK                     (0x7Fu)
#endif /* End (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) */

/* Control Register definitions */
#define debugOut_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define debugOut_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define debugOut_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define debugOut_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define debugOut_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define debugOut_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define debugOut_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define debugOut_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define debugOut_CTRL_HD_SEND               (uint8)(0x01u << debugOut_CTRL_HD_SEND_SHIFT)
#define debugOut_CTRL_HD_SEND_BREAK         (uint8)(0x01u << debugOut_CTRL_HD_SEND_BREAK_SHIFT)
#define debugOut_CTRL_MARK                  (uint8)(0x01u << debugOut_CTRL_MARK_SHIFT)
#define debugOut_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << debugOut_CTRL_PARITY_TYPE0_SHIFT)
#define debugOut_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << debugOut_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define debugOut_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define debugOut_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define debugOut_SEND_BREAK                         (0x00u)
#define debugOut_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define debugOut_REINIT                             (0x02u)
#define debugOut_SEND_WAIT_REINIT                   (0x03u)

#define debugOut_OVER_SAMPLE_8                      (8u)
#define debugOut_OVER_SAMPLE_16                     (16u)

#define debugOut_BIT_CENTER                         (debugOut_OVER_SAMPLE_COUNT - 2u)

#define debugOut_FIFO_LENGTH                        (4u)
#define debugOut_NUMBER_OF_START_BIT                (1u)
#define debugOut_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define debugOut_TXBITCTR_BREAKBITS8X   ((debugOut_BREAK_BITS_TX * debugOut_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define debugOut_TXBITCTR_BREAKBITS ((debugOut_BREAK_BITS_TX * debugOut_OVER_SAMPLE_COUNT) - 1u)

#define debugOut_HALF_BIT_COUNT   \
                            (((debugOut_OVER_SAMPLE_COUNT / 2u) + (debugOut_USE23POLLING * 1u)) - 2u)
#if (debugOut_OVER_SAMPLE_COUNT == debugOut_OVER_SAMPLE_8)
    #define debugOut_HD_TXBITCTR_INIT   (((debugOut_BREAK_BITS_TX + \
                            debugOut_NUMBER_OF_START_BIT) * debugOut_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define debugOut_RXBITCTR_INIT  ((((debugOut_BREAK_BITS_RX + debugOut_NUMBER_OF_START_BIT) \
                            * debugOut_OVER_SAMPLE_COUNT) + debugOut_HALF_BIT_COUNT) - 1u)

#else /* debugOut_OVER_SAMPLE_COUNT == debugOut_OVER_SAMPLE_16 */
    #define debugOut_HD_TXBITCTR_INIT   ((8u * debugOut_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define debugOut_RXBITCTR_INIT      (((7u * debugOut_OVER_SAMPLE_COUNT) - 1u) + \
                                                      debugOut_HALF_BIT_COUNT)
#endif /* End debugOut_OVER_SAMPLE_COUNT */

#define debugOut_HD_RXBITCTR_INIT                   debugOut_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 debugOut_initVar;
#if (debugOut_TX_INTERRUPT_ENABLED && debugOut_TX_ENABLED)
    extern volatile uint8 debugOut_txBuffer[debugOut_TX_BUFFER_SIZE];
    extern volatile uint8 debugOut_txBufferRead;
    extern uint8 debugOut_txBufferWrite;
#endif /* (debugOut_TX_INTERRUPT_ENABLED && debugOut_TX_ENABLED) */
#if (debugOut_RX_INTERRUPT_ENABLED && (debugOut_RX_ENABLED || debugOut_HD_ENABLED))
    extern uint8 debugOut_errorStatus;
    extern volatile uint8 debugOut_rxBuffer[debugOut_RX_BUFFER_SIZE];
    extern volatile uint8 debugOut_rxBufferRead;
    extern volatile uint8 debugOut_rxBufferWrite;
    extern volatile uint8 debugOut_rxBufferLoopDetect;
    extern volatile uint8 debugOut_rxBufferOverflow;
    #if (debugOut_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 debugOut_rxAddressMode;
        extern volatile uint8 debugOut_rxAddressDetected;
    #endif /* (debugOut_RXHW_ADDRESS_ENABLED) */
#endif /* (debugOut_RX_INTERRUPT_ENABLED && (debugOut_RX_ENABLED || debugOut_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define debugOut__B_UART__AM_SW_BYTE_BYTE 1
#define debugOut__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define debugOut__B_UART__AM_HW_BYTE_BY_BYTE 3
#define debugOut__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define debugOut__B_UART__AM_NONE 0

#define debugOut__B_UART__NONE_REVB 0
#define debugOut__B_UART__EVEN_REVB 1
#define debugOut__B_UART__ODD_REVB 2
#define debugOut__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define debugOut_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define debugOut_NUMBER_OF_STOP_BITS    (1u)

#if (debugOut_RXHW_ADDRESS_ENABLED)
    #define debugOut_RX_ADDRESS_MODE    (0u)
    #define debugOut_RX_HW_ADDRESS1     (0u)
    #define debugOut_RX_HW_ADDRESS2     (0u)
#endif /* (debugOut_RXHW_ADDRESS_ENABLED) */

#define debugOut_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << debugOut_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << debugOut_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << debugOut_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << debugOut_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << debugOut_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << debugOut_RX_STS_BREAK_SHIFT) \
                                        | (0 << debugOut_RX_STS_OVERRUN_SHIFT))

#define debugOut_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << debugOut_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << debugOut_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << debugOut_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << debugOut_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define debugOut_CONTROL_REG \
                            (* (reg8 *) debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define debugOut_CONTROL_PTR \
                            (  (reg8 *) debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(debugOut_TX_ENABLED)
    #define debugOut_TXDATA_REG          (* (reg8 *) debugOut_BUART_sTX_TxShifter_u0__F0_REG)
    #define debugOut_TXDATA_PTR          (  (reg8 *) debugOut_BUART_sTX_TxShifter_u0__F0_REG)
    #define debugOut_TXDATA_AUX_CTL_REG  (* (reg8 *) debugOut_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define debugOut_TXDATA_AUX_CTL_PTR  (  (reg8 *) debugOut_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define debugOut_TXSTATUS_REG        (* (reg8 *) debugOut_BUART_sTX_TxSts__STATUS_REG)
    #define debugOut_TXSTATUS_PTR        (  (reg8 *) debugOut_BUART_sTX_TxSts__STATUS_REG)
    #define debugOut_TXSTATUS_MASK_REG   (* (reg8 *) debugOut_BUART_sTX_TxSts__MASK_REG)
    #define debugOut_TXSTATUS_MASK_PTR   (  (reg8 *) debugOut_BUART_sTX_TxSts__MASK_REG)
    #define debugOut_TXSTATUS_ACTL_REG   (* (reg8 *) debugOut_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define debugOut_TXSTATUS_ACTL_PTR   (  (reg8 *) debugOut_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(debugOut_TXCLKGEN_DP)
        #define debugOut_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define debugOut_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define debugOut_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define debugOut_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define debugOut_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define debugOut_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define debugOut_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define debugOut_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define debugOut_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define debugOut_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) debugOut_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* debugOut_TXCLKGEN_DP */

#endif /* End debugOut_TX_ENABLED */

#if(debugOut_HD_ENABLED)

    #define debugOut_TXDATA_REG             (* (reg8 *) debugOut_BUART_sRX_RxShifter_u0__F1_REG )
    #define debugOut_TXDATA_PTR             (  (reg8 *) debugOut_BUART_sRX_RxShifter_u0__F1_REG )
    #define debugOut_TXDATA_AUX_CTL_REG     (* (reg8 *) debugOut_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define debugOut_TXDATA_AUX_CTL_PTR     (  (reg8 *) debugOut_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define debugOut_TXSTATUS_REG           (* (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_REG )
    #define debugOut_TXSTATUS_PTR           (  (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_REG )
    #define debugOut_TXSTATUS_MASK_REG      (* (reg8 *) debugOut_BUART_sRX_RxSts__MASK_REG )
    #define debugOut_TXSTATUS_MASK_PTR      (  (reg8 *) debugOut_BUART_sRX_RxSts__MASK_REG )
    #define debugOut_TXSTATUS_ACTL_REG      (* (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define debugOut_TXSTATUS_ACTL_PTR      (  (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End debugOut_HD_ENABLED */

#if( (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) )
    #define debugOut_RXDATA_REG             (* (reg8 *) debugOut_BUART_sRX_RxShifter_u0__F0_REG )
    #define debugOut_RXDATA_PTR             (  (reg8 *) debugOut_BUART_sRX_RxShifter_u0__F0_REG )
    #define debugOut_RXADDRESS1_REG         (* (reg8 *) debugOut_BUART_sRX_RxShifter_u0__D0_REG )
    #define debugOut_RXADDRESS1_PTR         (  (reg8 *) debugOut_BUART_sRX_RxShifter_u0__D0_REG )
    #define debugOut_RXADDRESS2_REG         (* (reg8 *) debugOut_BUART_sRX_RxShifter_u0__D1_REG )
    #define debugOut_RXADDRESS2_PTR         (  (reg8 *) debugOut_BUART_sRX_RxShifter_u0__D1_REG )
    #define debugOut_RXDATA_AUX_CTL_REG     (* (reg8 *) debugOut_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define debugOut_RXBITCTR_PERIOD_REG    (* (reg8 *) debugOut_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define debugOut_RXBITCTR_PERIOD_PTR    (  (reg8 *) debugOut_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define debugOut_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) debugOut_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define debugOut_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) debugOut_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define debugOut_RXBITCTR_COUNTER_REG   (* (reg8 *) debugOut_BUART_sRX_RxBitCounter__COUNT_REG )
    #define debugOut_RXBITCTR_COUNTER_PTR   (  (reg8 *) debugOut_BUART_sRX_RxBitCounter__COUNT_REG )

    #define debugOut_RXSTATUS_REG           (* (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_REG )
    #define debugOut_RXSTATUS_PTR           (  (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_REG )
    #define debugOut_RXSTATUS_MASK_REG      (* (reg8 *) debugOut_BUART_sRX_RxSts__MASK_REG )
    #define debugOut_RXSTATUS_MASK_PTR      (  (reg8 *) debugOut_BUART_sRX_RxSts__MASK_REG )
    #define debugOut_RXSTATUS_ACTL_REG      (* (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define debugOut_RXSTATUS_ACTL_PTR      (  (reg8 *) debugOut_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) */

#if(debugOut_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define debugOut_INTCLOCK_CLKEN_REG     (* (reg8 *) debugOut_IntClock__PM_ACT_CFG)
    #define debugOut_INTCLOCK_CLKEN_PTR     (  (reg8 *) debugOut_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define debugOut_INTCLOCK_CLKEN_MASK    debugOut_IntClock__PM_ACT_MSK
#endif /* End debugOut_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(debugOut_TX_ENABLED)
    #define debugOut_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End debugOut_TX_ENABLED */

#if(debugOut_HD_ENABLED)
    #define debugOut_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End debugOut_HD_ENABLED */

#if( (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) )
    #define debugOut_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define debugOut_TXBUFFERSIZE   debugOut_TX_BUFFER_SIZE
#define debugOut_RXBUFFERSIZE   debugOut_RX_BUFFER_SIZE

#if (debugOut_RXHW_ADDRESS_ENABLED)
    #define debugOut_RXADDRESSMODE  debugOut_RX_ADDRESS_MODE
    #define debugOut_RXHWADDRESS1   debugOut_RX_HW_ADDRESS1
    #define debugOut_RXHWADDRESS2   debugOut_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define debugOut_RXAddressMode  debugOut_RXADDRESSMODE
#endif /* (debugOut_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define debugOut_initvar                    debugOut_initVar

#define debugOut_RX_Enabled                 debugOut_RX_ENABLED
#define debugOut_TX_Enabled                 debugOut_TX_ENABLED
#define debugOut_HD_Enabled                 debugOut_HD_ENABLED
#define debugOut_RX_IntInterruptEnabled     debugOut_RX_INTERRUPT_ENABLED
#define debugOut_TX_IntInterruptEnabled     debugOut_TX_INTERRUPT_ENABLED
#define debugOut_InternalClockUsed          debugOut_INTERNAL_CLOCK_USED
#define debugOut_RXHW_Address_Enabled       debugOut_RXHW_ADDRESS_ENABLED
#define debugOut_OverSampleCount            debugOut_OVER_SAMPLE_COUNT
#define debugOut_ParityType                 debugOut_PARITY_TYPE

#if( debugOut_TX_ENABLED && (debugOut_TXBUFFERSIZE > debugOut_FIFO_LENGTH))
    #define debugOut_TXBUFFER               debugOut_txBuffer
    #define debugOut_TXBUFFERREAD           debugOut_txBufferRead
    #define debugOut_TXBUFFERWRITE          debugOut_txBufferWrite
#endif /* End debugOut_TX_ENABLED */
#if( ( debugOut_RX_ENABLED || debugOut_HD_ENABLED ) && \
     (debugOut_RXBUFFERSIZE > debugOut_FIFO_LENGTH) )
    #define debugOut_RXBUFFER               debugOut_rxBuffer
    #define debugOut_RXBUFFERREAD           debugOut_rxBufferRead
    #define debugOut_RXBUFFERWRITE          debugOut_rxBufferWrite
    #define debugOut_RXBUFFERLOOPDETECT     debugOut_rxBufferLoopDetect
    #define debugOut_RXBUFFER_OVERFLOW      debugOut_rxBufferOverflow
#endif /* End debugOut_RX_ENABLED */

#ifdef debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define debugOut_CONTROL                debugOut_CONTROL_REG
#endif /* End debugOut_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(debugOut_TX_ENABLED)
    #define debugOut_TXDATA                 debugOut_TXDATA_REG
    #define debugOut_TXSTATUS               debugOut_TXSTATUS_REG
    #define debugOut_TXSTATUS_MASK          debugOut_TXSTATUS_MASK_REG
    #define debugOut_TXSTATUS_ACTL          debugOut_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(debugOut_TXCLKGEN_DP)
        #define debugOut_TXBITCLKGEN_CTR        debugOut_TXBITCLKGEN_CTR_REG
        #define debugOut_TXBITCLKTX_COMPLETE    debugOut_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define debugOut_TXBITCTR_PERIOD        debugOut_TXBITCTR_PERIOD_REG
        #define debugOut_TXBITCTR_CONTROL       debugOut_TXBITCTR_CONTROL_REG
        #define debugOut_TXBITCTR_COUNTER       debugOut_TXBITCTR_COUNTER_REG
    #endif /* debugOut_TXCLKGEN_DP */
#endif /* End debugOut_TX_ENABLED */

#if(debugOut_HD_ENABLED)
    #define debugOut_TXDATA                 debugOut_TXDATA_REG
    #define debugOut_TXSTATUS               debugOut_TXSTATUS_REG
    #define debugOut_TXSTATUS_MASK          debugOut_TXSTATUS_MASK_REG
    #define debugOut_TXSTATUS_ACTL          debugOut_TXSTATUS_ACTL_REG
#endif /* End debugOut_HD_ENABLED */

#if( (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) )
    #define debugOut_RXDATA                 debugOut_RXDATA_REG
    #define debugOut_RXADDRESS1             debugOut_RXADDRESS1_REG
    #define debugOut_RXADDRESS2             debugOut_RXADDRESS2_REG
    #define debugOut_RXBITCTR_PERIOD        debugOut_RXBITCTR_PERIOD_REG
    #define debugOut_RXBITCTR_CONTROL       debugOut_RXBITCTR_CONTROL_REG
    #define debugOut_RXBITCTR_COUNTER       debugOut_RXBITCTR_COUNTER_REG
    #define debugOut_RXSTATUS               debugOut_RXSTATUS_REG
    #define debugOut_RXSTATUS_MASK          debugOut_RXSTATUS_MASK_REG
    #define debugOut_RXSTATUS_ACTL          debugOut_RXSTATUS_ACTL_REG
#endif /* End  (debugOut_RX_ENABLED) || (debugOut_HD_ENABLED) */

#if(debugOut_INTERNAL_CLOCK_USED)
    #define debugOut_INTCLOCK_CLKEN         debugOut_INTCLOCK_CLKEN_REG
#endif /* End debugOut_INTERNAL_CLOCK_USED */

#define debugOut_WAIT_FOR_COMLETE_REINIT    debugOut_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_debugOut_H */


/* [] END OF FILE */
