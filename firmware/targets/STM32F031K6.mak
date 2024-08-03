# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the STM32F031K6 Microcontroller

# Version: 20220909

# import compiler settings for the core in this microcontroller
include targets/core_CortexM0.mak

# Specific C files and linker scripts
FILES += targets/src/STM32F031K6.cpp targets/src/startup.cpp
DEFINES += -DMCU_$(MCU)
LDSCRIPT = -T"targets/ld/STM32F031K6.ld"

