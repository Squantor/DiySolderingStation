# # Proof of concept JBC T245 and T115 temperature control circuit
Most circuits here are copied/adapted from the [reverse engineered CD-2BC](https://www.eevblog.com/forum/testgear/jbc-soldering-station-cd-2bc-complete-schematic-analysis/) schematic.
# HSI (Hardware Software Interface)
* ADC voltage reference is 3V REF3030AIDBZT
* Crystal connected to pin 0_08 and 0_09
* Pin 0_24: UART RX connected to CH340B TX
* Pin 0_25: UART TX connected to CH340B RX
* Pin 0_12: Bootloader pin connected to switch with 10K pullup and 100nF capacitor, switch impedance is 100Ohm.
## TODO's
Still some things need to be done:
* schematic entry 
* PCB layout
* Review with one night in between
* Produce at [OSHPARK](https://oshpark.com/)
* Assemble
* Test & characterise
* update Readme.md with pictures and BOM
## BOM
TODO
* LM358 SOIC/TSSOP
* OP07 SOIC/TSSOP
* SY8120 DCDC converter
* bunch of zeners
* bunch of NPN/PNP power transistors

