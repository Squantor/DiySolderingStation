/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/* */
MEMORY
{
    flash :   ORIGIN = 0x00000000, LENGTH = 4K
    ram   :   ORIGIN = 0x10000000, LENGTH = 1K
}

/* Include main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript.ld
