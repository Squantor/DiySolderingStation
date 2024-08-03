# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the RP2040 Microcontroller

# Version: 20220916

# import compiler settings for the core in this microcontroller
include targets/core_CortexM0plus.mak
include targets/RP2040_flash.mak

# Specific C files and linker scripts
FILES += targets/src/RP2040.cpp \
         targets/src/startup.cpp \
				 targets/src/RP2040_boot2_$(FLASH).S
DEFINES += -DMCU_$(MCU)
LDSCRIPT = -T"targets/ld/RP2040_$(FLASH).ld"
INCLUDES += -Itargets/inc
