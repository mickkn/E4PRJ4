#ifndef  __Talkthrough_DEFINED
#define __Talkthrough_DEFINED

//--------------------------------------------------------------------------//
// Header files																//
//--------------------------------------------------------------------------//
#include <sys\exception.h>
#include <cdefBF533.h>
#include <ccblkfn.h>
#include <sysreg.h>
#include <sys/05000311.h>

#include <builtins.h>			//contains type fractional type
#include <fract2float_conv.h>	//contains float to fract conversion
#include <filter.h>				//contains filter functions
#include <math.h>				//contains powf
#include <stdio.h>				//contains printf

#include "Prefilter.h"
#include "RecBuf.h"
#include "Analyzer.h"
#include "Categorizer.h"
#include "Statistician.h"
#include "TwoWireCom.h"

//--------------------------------------------------------------------------//
// Symbolic constants														//
//--------------------------------------------------------------------------//
// addresses for Port B in Flash A
#define pFlashA_PortA_Dir	(volatile unsigned char *)0x20270006
#define pFlashA_PortA_Data	(volatile unsigned char *)0x20270004

// names for codec registers, used for iCodec1836TxRegs[]
#define DAC_CONTROL_1		0x0000
#define DAC_CONTROL_2		0x1000
#define DAC_VOLUME_0		0x2000
#define DAC_VOLUME_1		0x3000
#define DAC_VOLUME_2		0x4000
#define DAC_VOLUME_3		0x5000
#define DAC_VOLUME_4		0x6000
#define DAC_VOLUME_5		0x7000
#define ADC_0_PEAK_LEVEL	0x8000
#define ADC_1_PEAK_LEVEL	0x9000
#define ADC_2_PEAK_LEVEL	0xA000
#define ADC_3_PEAK_LEVEL	0xB000
#define ADC_CONTROL_1		0xC000
#define ADC_CONTROL_2		0xD000
#define ADC_CONTROL_3		0xE000

// names for slots in ad1836 audio frame
#define INTERNAL_ADC_L0			0
#define INTERNAL_ADC_L1			1
#define INTERNAL_ADC_R0			4
#define INTERNAL_ADC_R1			5
#define INTERNAL_DAC_L0			0
#define INTERNAL_DAC_L1			1
#define INTERNAL_DAC_L2			2
#define INTERNAL_DAC_R0			4
#define INTERNAL_DAC_R1			5
#define INTERNAL_DAC_R2			6

// size of array iCodec1836TxRegs and iCodec1836RxRegs
#define CODEC_1836_REGS_LENGTH	11

// SPI transfer mode
#define TIMOD_DMA_TX 0x0003

// SPORT0 word length
#define SLEN_32	0x001f

// DMA flow mode
#define FLOW_1	0x1000


// FlagA - defines
#define PASS_THROUGH	0
//#define FILTER_ACTIVE	1
#define FILTER_ACTIVE	1 // was 2
#define NUMBER_FLAGA_STATES	2 // was 3

//#define ANTAL_FILTKOEF 3

//--------------------------------------------------------------------------//
// Global variables															//
//--------------------------------------------------------------------------//
#define VAR_TYPE fract32

extern VAR_TYPE iChannel0LeftIn;
extern VAR_TYPE iChannel0RightIn;
extern VAR_TYPE iChannel0LeftOut;
extern VAR_TYPE iChannel0RightOut;
extern VAR_TYPE iChannel1LeftIn;
extern VAR_TYPE iChannel1RightIn;
extern VAR_TYPE iChannel1LeftOut;
extern VAR_TYPE iChannel1RightOut;
extern volatile short sCodec1836TxRegs[];
extern volatile VAR_TYPE iRxBuffer1[];
extern volatile VAR_TYPE iTxBuffer1[];

extern short FlagAMode;

//--------------------------------------------------------------------------//
// Prototypes																//
//--------------------------------------------------------------------------//
// in file Initialisation.c
void Init_EBIU(void);
void Init_Flash(void);
void Init1836(void);
void Init_Sport0(void);
void Init_DMA(void);
void Init_Interrupts(void);
void Enable_DMA_Sport0(void);
void Init_Flags(void);


// in file Process_data.c
void Process_Data(void);

// in file ISRs.c
EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
EX_INTERRUPT_HANDLER(FlagA_ISR);

#endif //__Talkthrough_DEFINED
