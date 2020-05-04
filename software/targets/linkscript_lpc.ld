/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
        FILL(0xff)
        KEEP(*(.cortex_vectors))
        KEEP(*(.vendor_vectors))
        . = ALIGN(4) ;
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
    .data : ALIGN(4)
    {
        FILL(0xff)
        _start_data = .;
        *(.ramfunc*) /* special section for RAM functions */
        *(.data*)
        _end_data = .;
    } >ram AT >rom

    .bss : ALIGN(4)
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
    /* create startup checksum, UM10800, chapter 3.6.2 */
    PROVIDE(__valid_user_code_checksum = 0 - 
                                         (_end_stack 
                                         + (Reset_Handler + 1) 
                                         + (NMI_Handler + 1) 
                                         + (HardFault_Handler + 1) 
                                         + (MemManage_Handler + 1) 
                                         + (BusFault_Handler + 1) 
                                         + (UsageFault_Handler + 1) 
                                         )
           );
    PROVIDE(_data_flash = LOADADDR(.data));
}

_end = .;
