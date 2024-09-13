# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20240223

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := unittests
$(NAME)_TARGET := PC
$(NAME)_DEFINES := -DMINUNIT_MAX_TESTS=1000
$(NAME)_LIBS := squantorMinUnit
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/test_ringbuf.cpp \
common/src/cmdline_simple.cpp \
$(PROJ_DIR)/src/test_cmdline_simple.cpp \
common/src/ansi_parse.cpp \
$(PROJ_DIR)/src/test_console.cpp \
$(PROJ_DIR)/src/test_ansi_parse.cpp \
$(PROJ_DIR)/src/test_command_interpreter.cpp \
$(PROJ_DIR)/src/test_command_value_stack.cpp \
$(PROJ_DIR)/src/test.cpp
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc -Icommon/inc
$(NAME)_PREBUILD_SCRIPT := $(PROJ_DIR)/prebuild.sh
$(NAME)_POSTBUILD_SCRIPT := $(PROJ_DIR)/postbuild.sh

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_DEFINES +=
