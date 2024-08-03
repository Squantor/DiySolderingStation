/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/* TODO: refer to datasheet memory map here */
MEMORY
{
    flash :   ORIGIN = 0x08000000, LENGTH = 64K
    ram   :   ORIGIN = 0x20000000, LENGTH = 20K
}

/* Include generic main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript.ld
