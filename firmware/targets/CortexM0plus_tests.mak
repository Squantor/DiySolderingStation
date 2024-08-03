# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for generic CortexM0+ controller but that actually is the
# LPC812, this is used for the libmcuCortexM0plus tests.

# Version: 20240202

# import compiler settings for the core in this microcontroller
include targets/core_CortexM0plus.mak

# Specific C files and linker scripts
FILES += targets/src/LPC812.cpp targets/src/startup.cpp
DEFINES += -DMCU_CortexM0plus
LDSCRIPT = -T"targets/ld/LPC812.ld"
