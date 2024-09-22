# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := POC_temp_sense
BOARD := POC_temp_sense_nuclone
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC845M301BD48
$(NAME)_DEFINES += 
$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/application.cpp \
$(PROJ_DIR)/src/command_handlers.cpp \
common/src/parse_digit.cpp \
$(PROJ_DIR)/src/command_stk.cpp \
$(PROJ_DIR)/src/command_empty.cpp \
$(PROJ_DIR)/src/command_drop.cpp \
$(PROJ_DIR)/src/command_dup.cpp \
$(PROJ_DIR)/src/command_stat.cpp \
$(PROJ_DIR)/src/command_mux.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc -Icommon/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)
