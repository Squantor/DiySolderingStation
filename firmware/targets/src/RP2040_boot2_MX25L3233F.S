/**
 * @file    RP2040_boot2_MX25L3233F.S
 * @brief   RP2040 second stage bootloader for MX25L3233F
 */

/**
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022 Bart Bilos 
 * For conditions of distribution and use, see LICENSE file
 */

#include <RP2040_defs.h>

#define CMD_READ 0xEB             /**< MX25L3233F flash read command */
#define CMD_READ_STATUS 0x05      /**< MX25L3233F read status register */
#define CMD_WRITE_ENABLE 0x06     /**< MX25L3233F write enable */
#define CMD_WRITE_STATUS 0x01     /**< MX25L3233F write status and configuration registers */
#define MODE_CONTINUOUS_READ 0xF0 /**< MX25L3233F continuous read mode bits */

#define STATUS_WEL_BITS (1<<1)  /**< MX25L3233F write latch enable bit */
#define STATUS_QE_BITS (1<<6)   /**< MX25L3233F write latch enable bit */

#define ADDR_LEN 8    /**< Address length (in 4bit increments) */
#define WAIT_CYCLES 4 /**< amount of wait cycles, includes mode bits! */

// RP2040 register settings
#define PICO_FLASH_SPI_CLKDIV 2

// SSI CTRLR0 setting for SPI: standard SPI format, 8bit dataframe, TX/RX read mode
#define CTRLR0_SPI (7 << 16) | (0 << 8)
// SSI CTRLR0 setting for XIP: QSPI format, 32bit dataframe, EEPROM read mode
#define CTRLR0_XIP (0x2 << 21) | (31 << 16) | (0x3 << 8)
// SSI CTRLR1 setting for XIP:
#define CTRLR1_XIP 0                                     
// SSI SPI CTRL0 setting for entering XIP: 4 wait cycles, 8 bit instruction, 32 bit address (8*4), cmd normal rest quad
#define SPI_CTRLR0_ENT (CMD_READ << 24) | (WAIT_CYCLES << 11) | (2 << 8) | (ADDR_LEN << 2) | (0x1 << 0)
// TODO: SSI SPI CTRL0 setting for XIP: 4 wait cycles, no instruction but append after address, 32 bit address (8*4), all in quad mode
#define SPI_CTRLR0_XIP (MODE_CONTINUOUS_READ << 24) | (WAIT_CYCLES << 11) | (0 << 8) | (ADDR_LEN << 2) | (0x2 << 0)

.cpu cortex-m0
.thumb

.section .boot.entry, "ax"

.global secondStageBoot
.type secondStageBoot,%function
.thumb_func
secondStageBoot:
  // Use r3 as SSI base address 
  ldr r3, =XIP_SSI_BASE

  // setup SSI in normal SPI mode
  // Disable SSI to allow config
  mov r1, #0
  str r1, [r3, #SSI_SSIENR_OFFSET]
  // Set baud rate
  mov r1, #PICO_FLASH_SPI_CLKDIV
  str r1, [r3, #SSI_BAUDR_OFFSET]
  // configure SPI mode
  ldr r1, =(CTRLR0_SPI)
  str r1, [r3, #SSI_CTRLR0_OFFSET]
  // Re-enable SSI, and select slave 0
  mov r1, #1
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // read out MX25L3233F status register
  ldr r0, =(CMD_READ_STATUS)
  // write command byte and dummy
  str r0, [r3, #SSI_DR0_OFFSET]
  str r0, [r3, #SSI_DR0_OFFSET]  
  bl wait_ssi_ready
  // read dummy and response
  ldr r0, [r3, #SSI_DR0_OFFSET]
  ldr r0, [r3, #SSI_DR0_OFFSET]
  // check if status register is set to accept QSPI commands
  movs r1, #STATUS_QE_BITS
  tst r1, r0
  bne qspi_enabled
  
  // MX25L3233F write enable
  ldr r0, =(CMD_WRITE_ENABLE)
  str r0, [r3, #SSI_DR0_OFFSET]
  bl wait_ssi_ready
 
  // MX25L3233F write status and config register
  ldr r0, =(CMD_WRITE_STATUS)
  str r0, [r3, #SSI_DR0_OFFSET]
  mov r0, #STATUS_QE_BITS
  str r0, [r3, #SSI_DR0_OFFSET]
  mov r0, #0
  str r0, [r3, #SSI_DR0_OFFSET]
  bl wait_ssi_ready

qspi_enabled:
  // configure SSI to emit a QSPI performance enhancing pattern
  // Disable SSI to allow further config
  mov r1, #0
  str r1, [r3, #SSI_SSIENR_OFFSET]
  // configure XIP mode
  ldr r1, =(CTRLR0_XIP)
  str r1, [r3, #SSI_CTRLR0_OFFSET]
  // configure XIP entry mode
  ldr r1, =(SPI_CTRLR0_ENT)
  ldr r0, =(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET)
  str r1, [r0]
  // NDF=0 (single 32b read)
  mov r1, #CTRLR1_XIP
  str r1, [r3, #SSI_CTRLR1_OFFSET]
  // Re-enable SSI
  mov r1, #1
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // send performance enhancing mode dummy read to MX25L3233F
  movs r1, #CMD_READ
  str r1, [r3, #SSI_DR0_OFFSET]
  movs r1, #MODE_CONTINUOUS_READ // this will be appended to address bits
  str r1, [r3, #SSI_DR0_OFFSET]
  bl wait_ssi_ready

  // configure SSI into XIP mode
  // Disable SSI to allow further config
  mov r1, #0
  str r1, [r3, #SSI_SSIENR_OFFSET]
  // configure XIP mode
  ldr r1, =(SPI_CTRLR0_XIP)
  ldr r0, =(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET)
  str r1, [r0]
  // Re-enable SSI
  mov r1, #1
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // flash is now mapped into memory space, we can now read and run

  // setup ISR vector table to correct position in VTOR of the PPB
  ldr r0, =(XIP_BASE + 0x100)
  ldr r1, =(PPB_BASE + M0PLUS_VTOR_OFFSET)
  str r0, [r1]
  // load stack pointer and entry from vector table into R0,R1
  ldmia r0, {r0, r1}  
  msr msp, r0         // load main stack pointer with reset vector value
  bx r1               // jump to entry point

// Pull in common routines
#include <RP2040_boot2_common.S>

.global literals
literals:
.ltorg

.end