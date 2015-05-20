# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Jeppe\Google Drev\E4PRJ4 gDrive\Vuggesystem arbejdsdokumenter\VuggeSinus\VuggeSinus.cydsn\VuggeSinus.cyprj
# Date: Wed, 20 May 2015 06:45:07 GMT
#set_units -time ns
create_clock -name {UART_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 13 25} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 1201 2401} [list [get_pins {ClockBlock/udb_div_3}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]


# Component constraints for C:\Users\Jeppe\Google Drev\E4PRJ4 gDrive\Vuggesystem arbejdsdokumenter\VuggeSinus\VuggeSinus.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Jeppe\Google Drev\E4PRJ4 gDrive\Vuggesystem arbejdsdokumenter\VuggeSinus\VuggeSinus.cydsn\VuggeSinus.cyprj
# Date: Wed, 20 May 2015 06:45:00 GMT