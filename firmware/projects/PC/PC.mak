# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20240223

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := PC
$(NAME)_TARGET := PC
$(NAME)_DEFINES := 
$(NAME)_LIBS :=
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/test.cpp \
$(PROJ_DIR)/src/test.c
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc
$(NAME)_PREBUILD_SCRIPT := $(PROJ_DIR)/prebuild.sh
$(NAME)_POSTBUILD_SCRIPT := $(PROJ_DIR)/postbuild.sh

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_DEFINES +=