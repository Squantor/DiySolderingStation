/**
 * @file    RP2040_defs.h
 * @brief   RP2040 common definitions
 */

/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#ifndef RP2040_DEFS_H
#define RP2040_DEFS_H

// RP2040 memory locations
#define XIP_SSI_BASE (0x18000000) /**< XIP SSI peripheral base address */
#define XIP_BASE (0x10000000)     /**< XIP memory base */
#define PPB_BASE (0xe0000000)     /**< Cortex-M0+ Internal Peripheral base address */
#define SRAM4_BASE (0x20040000)   /**< */
#define SRAM5_BASE (0x20041000)   /**< */

// RP2040 register offsets
#define SSI_CTRLR0_OFFSET (0x00)     /**< SSI control register 0 offset */
#define SSI_CTRLR1_OFFSET (0x04)     /**< SSI control register 1 offset */
#define SSI_SSIENR_OFFSET (0x08)     /**< SSI enable  register offset */
#define SSI_BAUDR_OFFSET (0x14)      /**< SSI baudrate register offset */
#define SSI_SR_OFFSET (0x28)         /**< SSI status register offset */
#define SSI_SR_TFE_BITS (1 << 2)     /**< SSI status TX Fifo empty bit */
#define SSI_SR_BUSY_BITS (1 << 0)    /**< SSI status busy bit */
#define SSI_DR0_OFFSET (0x60)        /**< SSI Data register 0 */
#define SSI_SPI_CTRLR0_OFFSET (0xf4) /**< SSI SPI control register 0 offset */
#define M0PLUS_VTOR_OFFSET (0xed08)  /**< Cortex M0 VTOR offset register */

#endif