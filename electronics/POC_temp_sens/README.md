# Proof of concept JBC T245 and T115 temperatature sensing circuit
JBC T245 handle thermocouple sensing circuit as copied/adapted from the [reverse engineered CD-2BC](https://www.eevblog.com/forum/testgear/jbc-soldering-station-cd-2bc-complete-schematic-analysis/) schematic. The PCB is made to imitate a 2.54mm pitch prototyping board cut to size to fit the prototype. On top of this protoboard a small size nuclone with LPC845 microcontroller is put on top.
# HSI (Hardware Software Interface)
* ADC voltage reference is 3V REF3030AIDBZT
* Crystal connected to pin 0_08 and 0_09
* Pin 0_24: UART RX connected to CH340B TX
* Pin 0_25: UART TX connected to CH340B RX
* Pin 0_12: Bootloader pin connected to switch with 10K pullup and 100nF capacitor, switch impedance is 100Ohm.
* Pin X_XX: 5V presence detection done with a resistive divider with 5.6K from 5V to 10K to ground
* Pin X_XX, Pin X_XX, Pin X_XX: 74HC4053 multiplexer 1
  * Mux setting 0:
  * Mux setting 1:
  * Mux setting 2:
  * Mux setting 3:
  * Mux setting 4:
  * Mux setting 5:
  * Mux setting 6:
  * Mux setting 7:
* Pin X_XX, Pin X_XX, Pin X_XX: 74HC4053 multiplexer 2
  * Mux setting 0:
  * Mux setting 1:
  * Mux setting 2:
  * Mux setting 3:
  * Mux setting 4:
  * Mux setting 5:
  * Mux setting 6:
  * Mux setting 7:
* Pin X_XX: Differential voltage with gain X from multiplexer 1 and 2, range X V and filtered by X kohm with X nF
# TODO's
* Building up prototype
* Test & characterise
* update Readme.md with pictures and BOM
# BOM
* OP07 opamp
* LM358 dual opamp
* 74HC4053 multiplexer
* [Small nuclone LPC845](https://github.com/Squantor/squantorDevelBoards/tree/master/electronics/nuclone_LPC845M301BD48_small) with USB2UART and serial flash, 3V ADC voltage reference.
# Pictures
# Measurements
