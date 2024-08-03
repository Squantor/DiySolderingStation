# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the a generic Cortex M4 microcontroller

# Version: 20220909

# import compiler settings for the core in this microcontroller
include targets/core_CortexM4.mak

# Specific C files and linker scripts
FILES += targets/src/core_CortexM4.cpp targets/src/startup.cpp
DEFINES += -DMCU_$(MCU)
LDSCRIPT = -T"targets/ld/core_CortexMgeneric.ld"
