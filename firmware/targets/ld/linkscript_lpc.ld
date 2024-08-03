/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*

Linker script specific for NXP microcontrollers, they have a special vector 
that holds a checksum.

Based on the unified cortex startup code by Paul Sokolovsky. Based on article 
by Vanya Sergeev http://dev.frozeneskimo.com/notes/cortex_cmsis/ , 
GNU ld documentation and numerous other public resources.

*/

ENTRY(Reset_Handler)

SECTIONS {

    .text : ALIGN(4)
    {
        KEEP(*(.cortex_vectors))
        KEEP(*(.vendor_vectors))
        . = ALIGN(4) ;
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
    } > flash

    /* http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
    .data : ALIGN(4)
    {
        _data_start = .;
        *(.ramfunc*)
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

    _stack_start = .;
    /* http://sourceware.org/binutils/docs/ld/MEMORY.html */
    PROVIDE(_stack_end = ORIGIN(ram) + LENGTH(ram));
    /* create startup checksum, UM10800, chapter 3.6.2 */
    PROVIDE(__valid_user_code_checksum = 0 - 
                                         (_stack_end
                                         + (Reset_Handler + 1) 
                                         + (NMI_Handler + 1) 
                                         + (HardFault_Handler + 1) 
                                         + (MemManage_Handler + 1) 
                                         + (BusFault_Handler + 1) 
                                         + (UsageFault_Handler + 1) 
                                         )
           );
    PROVIDE(_flash_data = LOADADDR(.data));
}

_end = .;
