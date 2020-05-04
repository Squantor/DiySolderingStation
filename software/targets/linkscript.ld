/*
 * Unified Cortex Startup - GNU ld linker script file
 *
 * This file is in public domain
 *
 * Put together by Paul Sokolovsky based on article by Vanya Sergeev
 * http://dev.frozeneskimo.com/notes/cortex_cmsis/ , GNU ld documentation
 * and numerous other public resources.
 *
 */

ENTRY(Reset_Handler)

SECTIONS {

    .text :
    {
        KEEP(*(.vectors))
        KEEP(*(.cortex_vectors))
        KEEP(*(.vendor_vectors))
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

        _end_text = .;
    } >rom

    /* http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
    .data :
    {
        _start_data = .;
        *(.ramfunc*) /* special section for RAM functions */
        *(.data*)
        _end_data = .;
    } >ram AT >rom

    .bss :
    {
        _start_bss = .;
        *(.bss*)
        *(COMMON)
        _end_bss = .;
    } >ram

    . = ALIGN(4);

    _start_stack = .;
    /* http://sourceware.org/binutils/docs/ld/MEMORY.html */
    PROVIDE(_end_stack = ORIGIN(ram) + LENGTH(ram));
    PROVIDE(_data_flash = LOADADDR(.data));
}

_end = .;
