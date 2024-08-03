# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the LPC1114_323 Microcontroller
#
# Version: 20220909

# import compiler settings for the core in this microcontroller
include targets/core_CortexM0.mak

# Specific C files and linker scripts
# TODO: add ROM patches for divison routines in the startup code
FILES += targets/src/LPC11XX_XLV.cpp targets/src/startup.cpp
DEFINES += -DMCU_$(MCU)
LDSCRIPT = -T"targets/ld/LPC1114_323.ld"

