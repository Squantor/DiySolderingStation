# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the Cortex-M0+ Core
#
# Version: 20220909

# Tool settings
include targets/TC_arm-none-eabi.mak

# Core flags
CFLAGS += -mcpu=cortex-m0plus -mthumb
CXXFLAGS += -mcpu=cortex-m0plus -mthumb
ASMFLAGS += -mcpu=cortex-m0plus -mthumb
LDFLAGS += -mcpu=cortex-m0plus -mthumb

