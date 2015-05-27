// ======================================================================
// VuggeSinus.v generated from TopDesign.cysch
// 05/20/2015 at 08:45
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PSOC4A 2
`define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17
`define CYDEV_CHIP_REV_PSOC4A_ES0 17
`define CYDEV_CHIP_DIE_PSOC5LP 3
`define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
`define CYDEV_CHIP_REV_PSOC5LP_ES0 0
`define CYDEV_CHIP_DIE_PANTHER 4
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_EXPECT 2
`define CYDEV_CHIP_REV_EXPECT 17
`define CYDEV_CHIP_DIE_ACTUAL 2
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_MEMBER_4D 2
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 3
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 4
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_MEMBER_5B 5
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 6
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_FAMILY_USED 2
`define CYDEV_CHIP_MEMBER_USED 3
`define CYDEV_CHIP_REVISION_USED 17
// Component: B_PWM_v3_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_20\B_PWM_v3_20.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_20"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_20\B_PWM_v3_20.v"
`endif

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// PWM_v3_20(CaptureMode=0, Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, Compare1_16=false, Compare1_8=true, Compare2_16=false, Compare2_8=false, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=65, CompareValue2=63, CONTROL3=0, ControlReg=true, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, DeadBand=1, DeadBand2_4=1, DeadBand256=0, DeadBandUsed=1, DeadTime=3, DitherOffset=0, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=199, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, Resolution=8, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, Status=true, TermMode_capture=0, TermMode_clock=0, TermMode_cmp_sel=0, TermMode_enable=0, TermMode_interrupt=0, TermMode_kill=0, TermMode_ph1=0, TermMode_ph2=0, TermMode_pwm=0, TermMode_pwm1=0, TermMode_pwm2=0, TermMode_reset=0, TermMode_tc=0, TermMode_trigger=0, TermVisibility_capture=false, TermVisibility_clock=true, TermVisibility_cmp_sel=false, TermVisibility_enable=false, TermVisibility_interrupt=true, TermVisibility_kill=false, TermVisibility_ph1=true, TermVisibility_ph2=true, TermVisibility_pwm=true, TermVisibility_pwm1=false, TermVisibility_pwm2=false, TermVisibility_reset=true, TermVisibility_tc=true, TermVisibility_trigger=false, TriggerMode=0, UDB16=false, UDB8=true, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP8, CY_COMPONENT_NAME=PWM_v3_20, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=PWM, CY_INSTANCE_SHORT_NAME=PWM, CY_MAJOR_VERSION=3, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.1 SP2, INSTANCE_NAME=PWM, )
module PWM_v3_20_0 (
    pwm2,
    tc,
    clock,
    reset,
    pwm1,
    interrupt,
    capture,
    kill,
    enable,
    trigger,
    cmp_sel,
    pwm,
    ph1,
    ph2);
    output      pwm2;
    output      tc;
    input       clock;
    input       reset;
    output      pwm1;
    output      interrupt;
    input       capture;
    input       kill;
    input       enable;
    input       trigger;
    input       cmp_sel;
    output      pwm;
    output      ph1;
    output      ph2;

    parameter Resolution = 8;

          wire  Net_227;
          wire  Net_226;
          wire  Net_225;
          wire  Net_224;
          wire  Net_223;
          wire  Net_222;
          wire  Net_139;
          wire  Net_138;
          wire  Net_135;
          wire  Net_178;
          wire  Net_181;
          wire  Net_179;
          wire  Net_180;
          wire  Net_183;
          wire  Net_186;
          wire  Net_68;
          wire  Net_125;

    B_PWM_v3_20 PWMUDB (
        .reset(Net_186),
        .clock(Net_68),
        .tc(tc),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(interrupt),
        .kill(Net_179),
        .capture(Net_180),
        .enable(Net_181),
        .cmp_sel(Net_183),
        .trigger(Net_178),
        .pwm(pwm),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 1;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 8;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_68 = clock;


    assign Net_139 = Net_125 | Net_138;

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_138));

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_179 = kill;

	// VMux_capture_1 (cy_virtualmux_v1_0)
	assign Net_183 = cmp_sel;

	// VMux_capture_2 (cy_virtualmux_v1_0)
	assign Net_180 = capture;

	// VMux_capture_3 (cy_virtualmux_v1_0)
	assign Net_181 = enable;

	// VMux_capture_4 (cy_virtualmux_v1_0)
	assign Net_178 = trigger;

	// VMux_capture_5 (cy_virtualmux_v1_0)
	assign Net_186 = reset;



endmodule

// Component: cy_constant_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0\cy_constant_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0\cy_constant_v1_0.v"
`endif

// SCB_P4_v2_0(ApplySbClockParam=false, BitWidthReplacementStringRx=uint8, BitWidthReplacementStringTx=uint8, BufNum=1, Clock_CheckTolerance=false, Clock_desired_freq=24000, Clock_desired_freq_unit=3, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, Cond=#, DBGW_SCB_IP_V0=true, DBGW_SCB_IP_V1=false, DBGW_SCB_IP_V2=false, EndCond=#endif, EzI2cBitWidthReplacementString=uint16, EzI2cBusVoltage=3.3, EzI2cByteModeEnable=false, EzI2cClkFreqDes=1550, EzI2cClockFromTerm=false, EzI2cClockStretching=true, EzI2cDataRate=100, EzI2cIsPrimarySlaveAddressHex=true, EzI2cIsSecondarySlaveAddressHex=true, EzI2cMedianFilterEnable=true, EzI2cNumberOfAddresses=0, EzI2cOvsFactor=16, EzI2cPrimarySlaveAddress=8, EzI2cSecondarySlaveAddress=9, EzI2cSlaveAddressMask=254, EzI2cSlewRate=0, EzI2cSubAddressSize=0, EzI2cWakeEnable=false, I2cAcceptAddress=false, I2cBusVoltage=3.3, I2cBusVoltageLevel=, I2cByteModeEnable=false, I2cClkFreqDes=1550, I2cClockFromTerm=false, I2cDataRate=100, I2cExternIntrHandler=false, I2cIsSlaveAddressHex=true, I2cIsSlaveAddressMaskHex=true, I2cManualOversampleControl=true, I2cMedianFilterEnable=true, I2cMode=1, I2cOvsFactor=16, I2cOvsFactorHigh=8, I2cOvsFactorLow=8, I2cSlaveAddress=8, I2cSlaveAddressMask=254, I2cSlewRate=0, I2cSlewRateSettings=0, I2cWakeEnable=false, PinName0Unconfig=spi_mosi_i2c_scl_uart_rx, PinName0UnconfigWake=spi_mosi_i2c_scl_uart_rx_wake, PinName1Unconfig=spi_miso_i2c_sda_uart_tx, PinName2Unconfig=spi_sclk, PinName3Unconfig=spi_ss0, RemoveI2cPins=true, RemoveMisoSdaTx=true, RemoveMosiSclRx=true, RemoveMosiSclRxWake=true, RemoveScbClk=false, RemoveScbIrq=true, RemoveSpiMasterPins=true, RemoveSpiMasterSs0Pin=true, RemoveSpiMasterSs1Pin=true, RemoveSpiMasterSs2Pin=true, RemoveSpiMasterSs3Pin=true, RemoveSpiSclk=true, RemoveSpiSlavePins=true, RemoveSpiSs0=true, RemoveSpiSs1=true, RemoveSpiSs2=true, RemoveSpiSs3=true, RemoveUartCtsPin=true, RemoveUartRtsPin=true, RemoveUartRxPin=false, RemoveUartRxTxPin=true, RemoveUartRxWake=true, RemoveUartRxWakeupIrq=true, RemoveUartTxPin=false, ScbClkFreqDes=1382.4, ScbClkMinusTolerance=5, ScbClkPlusTolerance=5, ScbClockSelect=1, ScbClockTermEnable=false, ScbCustomIntrHandlerEnable=true, ScbInterruptTermEnable=false, ScbMisoSdaTxEnable=true, ScbMode=4, ScbModeHw=2, ScbMosiSclRxEnable=true, ScbRxWakeIrqEnable=false, ScbSclkEnable=false, ScbSs0Enable=false, ScbSs1Enable=false, ScbSs2Enable=false, ScbSs3Enable=false, SpiBitRate=1000, SpiBitsOrder=1, SpiByteModeEnable=false, SpiClkFreqDes=16000, SpiClockFromTerm=false, SpiFreeRunningSclk=false, SpiInterruptMode=0, SpiIntrMasterSpiDone=false, SpiIntrRxFull=false, SpiIntrRxNotEmpty=false, SpiIntrRxOverflow=false, SpiIntrRxTrigger=false, SpiIntrRxUnderflow=false, SpiIntrSlaveBusError=false, SpiIntrTxEmpty=false, SpiIntrTxNotFull=false, SpiIntrTxOverflow=false, SpiIntrTxTrigger=false, SpiIntrTxUnderflow=false, SpiLateMisoSampleEnable=false, SpiManualOversampleControl=true, SpiMedianFilterEnable=false, SpiMode=0, SpiNumberOfRxDataBits=8, SpiNumberOfSelectLines=1, SpiNumberOfTxDataBits=8, SpiOvsFactor=16, SpiRxBufferSize=8, SpiRxIntrMask=0, SpiRxTriggerLevel=7, SpiSclkMode=0, SpiSs0Polarity=0, SpiSs1Polarity=0, SpiSs2Polarity=0, SpiSs3Polarity=0, SpiSubMode=0, SpiTransferSeparation=1, SpiTxBufferSize=8, SpiTxIntrMask=0, SpiTxTriggerLevel=0, SpiWakeEnable=false, TermMode_clock=0, TermMode_interrupt=0, TermVisibility_clock=false, TermVisibility_interrupt=false, UartByteModeEnable=false, UartClkFreqDes=1382.4, UartClockFromTerm=false, UartCtsEnable=false, UartCtsPolarity=0, UartDataRate=115200, UartDirection=3, UartDropOnFrameErr=false, UartDropOnParityErr=false, UartInterruptMode=0, UartIntrRxFrameErr=false, UartIntrRxFull=false, UartIntrRxNotEmpty=false, UartIntrRxOverflow=false, UartIntrRxParityErr=false, UartIntrRxTrigger=false, UartIntrRxUnderflow=false, UartIntrTxEmpty=false, UartIntrTxNotFull=false, UartIntrTxOverflow=false, UartIntrTxTrigger=false, UartIntrTxUartDone=false, UartIntrTxUartLostArb=false, UartIntrTxUartNack=false, UartIntrTxUnderflow=false, UartIrdaLowPower=false, UartIrdaPolarity=0, UartMedianFilterEnable=false, UartMpEnable=false, UartMpRxAcceptAddress=false, UartMpRxAddress=2, UartMpRxAddressMask=255, UartNumberOfDataBits=8, UartNumberOfStopBits=2, UartOvsFactor=12, UartParityType=2, UartRtsEnable=false, UartRtsPolarity=0, UartRtsTriggerLevel=4, UartRxBufferSize=8, UartRxEnable=true, UartRxIntrMask=0, UartRxTriggerLevel=7, UartSmCardRetryOnNack=false, UartSubMode=0, UartTxBufferSize=8, UartTxEnable=true, UartTxIntrMask=0, UartTxTriggerLevel=0, UartWakeEnable=false, CY_COMPONENT_NAME=SCB_P4_v2_0, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=UART, CY_INSTANCE_SHORT_NAME=UART, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.1 SP2, INSTANCE_NAME=UART, )
module SCB_P4_v2_0_1 (
    interrupt,
    clock);
    output      interrupt;
    input       clock;


          wire  Net_904;
          wire  Net_898;
          wire  Net_933;
          wire  uncfg_rx_irq;
          wire  Net_824;
          wire  Net_823;
          wire  Net_767;
          wire  Net_754;
          wire  rx_irq;
          wire [3:0] ss;
          wire  Net_682;
          wire  Net_676;
          wire  Net_458;
          wire  Net_896;
          wire  Net_903;
          wire  Net_932;
          wire  Net_855;
          wire  Net_422;
          wire  Net_467;
          wire  SCBclock;
          wire  Net_751;
          wire  Net_928;
          wire  Net_927;
          wire  Net_459;
          wire  Net_747;
          wire  Net_746;
          wire  Net_452;
          wire  Net_379;
          wire  Net_654;
          wire  Net_416;
          wire  Net_891;
          wire  Net_387;
          wire  Net_653;
          wire  Net_739;
          wire  Net_916;
          wire  Net_660;
          wire  Net_915;
          wire  Net_252;
          wire  Net_899;
          wire  Net_652;
          wire  Net_474;
          wire  Net_909;
          wire  Net_547;
          wire  Net_245;
          wire  Net_663;
          wire  Net_847;
          wire  Net_656;
          wire  Net_703;
          wire  Net_687;
          wire  Net_581;
          wire  Net_580;


	cy_clock_v1_0
		#(.id("43ec2fa1-bf22-4b71-9477-b6ca7b97f0b0/81fcee8a-3b8b-4be1-9a5f-a5e2e619a938"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("723379629.62963"),
		  .is_direct(0),
		  .is_digital(0))
		SCBCLK
		 (.clock_out(Net_847));


    ZeroTerminal ZeroTerminal_5 (
        .z(Net_459));

	// select_s_VM (cy_virtualmux_v1_0)
	assign Net_652 = Net_459;

    ZeroTerminal ZeroTerminal_4 (
        .z(Net_452));

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_676));

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_245));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_416));

	// rx_VM (cy_virtualmux_v1_0)
	assign Net_654 = Net_379;

	// rx_wake_VM (cy_virtualmux_v1_0)
	assign Net_682 = uncfg_rx_irq;

	// clock_VM (cy_virtualmux_v1_0)
	assign SCBclock = Net_847;

	// sclk_s_VM (cy_virtualmux_v1_0)
	assign Net_653 = Net_416;

	// mosi_s_VM (cy_virtualmux_v1_0)
	assign Net_909 = Net_676;

	// miso_m_VM (cy_virtualmux_v1_0)
	assign Net_663 = Net_245;

	wire [0:0] tmpOE__tx_net;
	wire [0:0] tmpFB_0__tx_net;
	wire [0:0] tmpIO_0__tx_net;
	wire [0:0] tmpINTERRUPT_0__tx_net;
	electrical [0:0] tmpSIOVREF__tx_net;

	cy_psoc3_pins_v1_10
		#(.id("43ec2fa1-bf22-4b71-9477-b6ca7b97f0b0/23b8206d-1c77-4e61-be4a-b4037d5de5fc"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("B"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		tx
		 (.oe(tmpOE__tx_net),
		  .y({Net_656}),
		  .fb({tmpFB_0__tx_net[0:0]}),
		  .io({tmpIO_0__tx_net[0:0]}),
		  .siovref(tmpSIOVREF__tx_net),
		  .interrupt({tmpINTERRUPT_0__tx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__tx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_754));


    assign Net_767 = Net_847 | Net_754;

	wire [0:0] tmpOE__rx_net;
	wire [0:0] tmpIO_0__rx_net;
	wire [0:0] tmpINTERRUPT_0__rx_net;
	electrical [0:0] tmpSIOVREF__rx_net;

	cy_psoc3_pins_v1_10
		#(.id("43ec2fa1-bf22-4b71-9477-b6ca7b97f0b0/78e33e5d-45ea-4b75-88d5-73274e8a7ce4"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		rx
		 (.oe(tmpOE__rx_net),
		  .y({1'b0}),
		  .fb({Net_379}),
		  .io({tmpIO_0__rx_net[0:0]}),
		  .siovref(tmpSIOVREF__rx_net),
		  .interrupt({tmpINTERRUPT_0__rx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__rx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	// cts_VM (cy_virtualmux_v1_0)
	assign Net_739 = Net_747;

    cy_m0s8_scb_v2_0 SCB (
        .rx(Net_654),
        .miso_m(Net_663),
        .select_m(ss[3:0]),
        .sclk_m(Net_687),
        .mosi_s(Net_909),
        .select_s(Net_652),
        .sclk_s(Net_653),
        .mosi_m(Net_660),
        .scl(Net_580),
        .sda(Net_581),
        .tx(Net_656),
        .miso_s(Net_703),
        .interrupt(interrupt),
        .cts(Net_739),
        .rts(Net_751),
        .tx_req(Net_823),
        .rx_req(Net_824),
        .clock(SCBclock));
    defparam SCB.scb_mode = 2;

    ZeroTerminal ZeroTerminal_6 (
        .z(Net_747));

	// Device_VM1 (cy_virtualmux_v1_0)
	assign Net_547 = Net_896;

	// Device_VM5 (cy_virtualmux_v1_0)
	assign Net_891 = Net_932;

	// Device_VM2 (cy_virtualmux_v1_0)
	assign Net_474 = Net_903;

	// Device_VM3 (cy_virtualmux_v1_0)
	assign Net_899 = Net_915;

	// Device_VM4 (cy_virtualmux_v1_0)
	assign uncfg_rx_irq = Net_927;



endmodule

// Component: B_Timer_v2_70
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_70"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_70\B_Timer_v2_70.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_70"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_70\B_Timer_v2_70.v"
`endif

// Timer_v2_70(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=true, CaptureMode=1, CONTROL3=0, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, DeviceFamily=PSoC4, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=false, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=0, NumberOfCaptures=1, param45=1, Period=199, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, Resolution=8, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=17, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=false, UDB8=true, UDBControlReg=true, UsesHWEnable=0, VerilogSectionReplacementString=sT8, CY_COMPONENT_NAME=Timer_v2_70, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Timer, CY_INSTANCE_SHORT_NAME=Timer, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=70, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.1 SP2, INSTANCE_NAME=Timer, )
module Timer_v2_70_2 (
    clock,
    reset,
    interrupt,
    enable,
    capture,
    trigger,
    capture_out,
    tc);
    input       clock;
    input       reset;
    output      interrupt;
    input       enable;
    input       capture;
    input       trigger;
    output      capture_out;
    output      tc;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC4";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 0;
    parameter Resolution = 8;
    parameter SiliconRevision = "17";


    B_Timer_v2_70 TimerUDB (
        .reset(reset),
        .interrupt(interrupt),
        .enable(enable),
        .trigger(trigger),
        .capture_in(capture),
        .capture_out(capture_out),
        .tc(tc),
        .clock(clock));
    defparam TimerUDB.Capture_Count = 2;
    defparam TimerUDB.CaptureCounterEnabled = 0;
    defparam TimerUDB.CaptureMode = 1;
    defparam TimerUDB.EnableMode = 0;
    defparam TimerUDB.InterruptOnCapture = 0;
    defparam TimerUDB.Resolution = 8;
    defparam TimerUDB.RunMode = 0;
    defparam TimerUDB.TriggerMode = 0;



endmodule

// top
module top ;

          wire  Net_852;
          wire  Net_909;
          wire  Net_908;
          wire  Net_907;
          wire  Net_906;
          wire  Net_905;
          wire  Net_903;
          wire  Net_398;
          wire  Net_397;
          wire  Net_688;
          wire  Net_746;
          wire  Net_741;
          wire  Net_740;
          wire  Net_739;
          wire  Net_738;
          wire  Net_737;
          wire  Net_736;
          wire  Net_735;
          wire  Net_734;
          wire  Net_733;
          wire  Net_757;
          wire  Net_755;
          wire  Net_777;
          wire  Net_12;
          wire  Net_745;
          wire  Net_744;

    PWM_v3_20_0 PWM (
        .reset(Net_744),
        .clock(Net_745),
        .tc(Net_733),
        .pwm1(Net_734),
        .pwm2(Net_735),
        .interrupt(Net_736),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_746),
        .ph1(Net_755),
        .ph2(Net_757));
    defparam PWM.Resolution = 8;

    assign Net_744 = 1'h0;


	cy_clock_v1_0
		#(.id("9d6bd674-378c-4770-889f-ab6e1e023079"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("250000000"),
		  .is_direct(0),
		  .is_digital(1))
		Clock_1
		 (.clock_out(Net_745));


    SCB_P4_v2_0_1 UART (
        .interrupt(Net_397),
        .clock(1'b0));

	wire [0:0] tmpOE__Pin_1_net;
	wire [0:0] tmpFB_0__Pin_1_net;
	wire [0:0] tmpIO_0__Pin_1_net;
	wire [0:0] tmpINTERRUPT_0__Pin_1_net;
	electrical [0:0] tmpSIOVREF__Pin_1_net;

	cy_psoc3_pins_v1_10
		#(.id("7c34c6cf-4a06-49b5-ab2a-2fd17e3f0d60"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		Pin_1
		 (.oe(tmpOE__Pin_1_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Pin_1_net[0:0]}),
		  .io({tmpIO_0__Pin_1_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_1_net),
		  .interrupt({tmpINTERRUPT_0__Pin_1_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Pin_1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PWM_A_net;
	wire [0:0] tmpFB_0__PWM_A_net;
	wire [0:0] tmpIO_0__PWM_A_net;
	wire [0:0] tmpINTERRUPT_0__PWM_A_net;
	electrical [0:0] tmpSIOVREF__PWM_A_net;

	cy_psoc3_pins_v1_10
		#(.id("f21f6278-5cde-4501-9d67-475737a5efa0"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		PWM_A
		 (.oe(tmpOE__PWM_A_net),
		  .y({Net_755}),
		  .fb({tmpFB_0__PWM_A_net[0:0]}),
		  .io({tmpIO_0__PWM_A_net[0:0]}),
		  .siovref(tmpSIOVREF__PWM_A_net),
		  .interrupt({tmpINTERRUPT_0__PWM_A_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__PWM_A_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PWM_B_net;
	wire [0:0] tmpFB_0__PWM_B_net;
	wire [0:0] tmpIO_0__PWM_B_net;
	wire [0:0] tmpINTERRUPT_0__PWM_B_net;
	electrical [0:0] tmpSIOVREF__PWM_B_net;

	cy_psoc3_pins_v1_10
		#(.id("c70725f4-6980-443c-9e03-db92596fc85c"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		PWM_B
		 (.oe(tmpOE__PWM_B_net),
		  .y({Net_757}),
		  .fb({tmpFB_0__PWM_B_net[0:0]}),
		  .io({tmpIO_0__PWM_B_net[0:0]}),
		  .siovref(tmpSIOVREF__PWM_B_net),
		  .interrupt({tmpINTERRUPT_0__PWM_B_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__PWM_B_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("920ac626-75fc-42be-bddc-386ba9cec7f2"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("25000000000"),
		  .is_direct(0),
		  .is_digital(1))
		timer_clock
		 (.clock_out(Net_777));


    ZeroTerminal ZeroTerminal_1 (
        .z(Net_12));

    Timer_v2_70_2 Timer (
        .reset(Net_12),
        .interrupt(Net_905),
        .enable(1'b1),
        .trigger(1'b1),
        .capture(1'b0),
        .capture_out(Net_909),
        .tc(Net_852),
        .clock(Net_777));
    defparam Timer.CaptureCount = 2;
    defparam Timer.CaptureCounterEnabled = 0;
    defparam Timer.DeviceFamily = "PSoC4";
    defparam Timer.InterruptOnCapture = 0;
    defparam Timer.InterruptOnTC = 0;
    defparam Timer.Resolution = 8;
    defparam Timer.SiliconRevision = "17";


	cy_isr_v1_0
		#(.int_type(2'b00))
		isr_1
		 (.int_signal(Net_852));


	wire [0:0] tmpOE__ISR_Pin_net;
	wire [0:0] tmpFB_0__ISR_Pin_net;
	wire [0:0] tmpIO_0__ISR_Pin_net;
	wire [0:0] tmpINTERRUPT_0__ISR_Pin_net;
	electrical [0:0] tmpSIOVREF__ISR_Pin_net;

	cy_psoc3_pins_v1_10
		#(.id("e851a3b9-efb8-48be-bbb8-b303b216c393"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		ISR_Pin
		 (.oe(tmpOE__ISR_Pin_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__ISR_Pin_net[0:0]}),
		  .io({tmpIO_0__ISR_Pin_net[0:0]}),
		  .siovref(tmpSIOVREF__ISR_Pin_net),
		  .interrupt({tmpINTERRUPT_0__ISR_Pin_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__ISR_Pin_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule

