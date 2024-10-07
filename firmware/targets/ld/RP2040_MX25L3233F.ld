/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
RP2040 linkerfile code, inspired by the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
More information taken from raspberry Pi Pico SDK
*/

/*
We reserve the top of flash to put the second stage loader there. This gets loaded by the 
first stage bootloader in Core0stack but are not aware of this and it does not matter as the
bootloader is position independent.
The Pico SDK makes a separate bin file that gets compiled and converted into a binary array and
then linked in the right position.
 */
MEMORY
{
  flash (rx) : ORIGIN = 0x10000000, LENGTH = 4096K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
  core0Stack (rwx) : ORIGIN = 0x20040000, LENGTH = 4k
  core1Stack (rwx) : ORIGIN = 0x20041000, LENGTH = 4k
}

BOOTLOADER_CRC = 0x7427b4A2; /* Computed CRC by bin2uf2*/

/* Include main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript_rp2040.ld
