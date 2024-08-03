/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/* UM10398 Table 4 + Chapter 2.2 Memory map */
MEMORY
{
    flash :   ORIGIN = 0x00000000, LENGTH = 48K
    ram   :   ORIGIN = 0x10000000, LENGTH = 8K
}

/* Include main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript_lpc.ld
