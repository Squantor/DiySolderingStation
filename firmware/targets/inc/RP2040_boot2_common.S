/**
 * @file    RP2040_boot2_common.S
 * @brief   RP2040 second stage bootloader common routines
 */

/**
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022 Bart Bilos 
 * For conditions of distribution and use, see LICENSE file
 */

#ifndef RP2040_BOOT2_COMMON_S
#define RP2040_BOOT2_COMMON_S

/** @brief wait until SSI is ready
 *  inputs: r3: SSI base register
 *  clobbers: none
 *
 */
.type wait_ssi_ready,%function
.thumb_func
wait_ssi_ready:
    push {r0, r1, lr}

    // repeat until TFE and BUSY are not set
wait_again:
    ldr r1, [r3, #SSI_SR_OFFSET]
    movs r0, #SSI_SR_TFE_BITS
    tst r1, r0
    beq wait_again
    movs r0, #SSI_SR_BUSY_BITS
    tst r1, r0
    bne wait_again

    pop {r0, r1, pc}

#endif
