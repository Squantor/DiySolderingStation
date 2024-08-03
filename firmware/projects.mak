# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all libraries
include $(BASE_DIR)/projects/PC/PC.mak
include $(BASE_DIR)/projects/DiySolder_LPC845/DiySolder_LPC845.mak
