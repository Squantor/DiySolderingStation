/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
RP2040 linkerfile code, inspired by the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
More information taken from raspberry Pi Pico SDK
*/

ENTRY(secondStageBoot)

SECTIONS {

  .flash_begin : 
  {
    __flash_binary_start = .;
  } > flash

  .boot2 : ALIGN(4) 
  {
    _boot2_start = .;
    KEEP(*(.boot.entry))
    . = 256-4;
    LONG(0xDEADBEEF) /* Insert dummy CRC */
    _boot2_end = .;
  } > flash

  ASSERT(_boot2_end - _boot2_start == 256, "ERROR: Second stage bootloader not 256 bytes!")
 
  .text : ALIGN(4)
  {
    _text_start = .;
    KEEP(*(.cortex_vectors))
    KEEP(*(.vendor_vectors))
    *(.romfunc*)
    *(.text*)
    *(.rodata*)

    /* C++ constructors etc */
    . = ALIGN(4);
    KEEP(*(.init))
    
    . = ALIGN(4);
    __preinit_array_start = .;
    KEEP (*(.preinit_array))
    __preinit_array_end = .;
    
    . = ALIGN(4);
    __init_array_start = .;
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    __init_array_end = .;
    
    KEEP(*(.fini));
    
    . = ALIGN(4);
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))
    
    . = ALIGN(4);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))
    . = ALIGN(4);
    /* End C++ */

    _text_end = .;
  /*} > ram AT > flash*/
  } > flash

  /* http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
  .data : ALIGN(4)
  {
    _data_start = .;
    *(.ramfunc*) /* special section for RAM functions */
    *(.data*)
    _data_end = .;
  } > ram AT > flash

  .bss : ALIGN(4)
  {
    _bss_start = .;
    *(.bss*)
    *(COMMON)
    _bss_end = .;
  } > ram

  . = ALIGN(4);

  _start_stack = .;
  /* http://sourceware.org/binutils/docs/ld/MEMORY.html */
  PROVIDE(_stack_end = ORIGIN(core0Stack) + LENGTH(core0Stack));
  PROVIDE(_flash_data = LOADADDR(.data));
  PROVIDE(_flash_start = ORIGIN(flash));
}

_end = .;
