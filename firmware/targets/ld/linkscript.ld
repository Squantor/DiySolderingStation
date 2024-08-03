/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

ENTRY(Reset_Handler)

SECTIONS {

    .text :
    {
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
    } > flash

    /* http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
    .data :
    {
        _data_start = .;
        *(.ramfunc*) /* special section for RAM functions */
        *(.data*)
        _data_end = .;
    } > ram AT > flash

    .bss :
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
    PROVIDE(_flash_data = LOADADDR(.data));
}

_end = .;
