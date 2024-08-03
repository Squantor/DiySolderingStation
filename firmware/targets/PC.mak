# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the PC target
#
# Version: 20230127

# Tool settings
include targets/TC_local.mak

# valid configurations like debug, release test, etcetera
CONFIGS := debug release

#default flags
CFLAGS := -std=gnu11 -Wall -Wextra -c
CFLAGS_debug := -O0 -g3
CFLAGS_release := -O2 -g
CXXFLAGS := -std=c++20 -Wall -Wextra -c
CXXFLAGS_debug := -O0 -g3
CXXFLAGS_release := -O2 -g
ASMFLAGS := -c -x assembler-with-cpp
LDFLAGS +=
LDSCRIPT :=
DEFINES_release += -DNDEBUG
DEFINES_debug += -DDEBUG
DEFINES += $($(PROJECT)_DEFINES)
FILES_debug := 
FILES_release := 
TARGET_LIBRARIES :=
