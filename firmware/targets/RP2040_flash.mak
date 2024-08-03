# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Flash chip boot2 handling for the RP2040 Microcontroller

# Version: 20221229

FLASH_CHIPS := generic MX25L3233F

# collect flash chip configuration information
ifndef $(PROJECT)_FLASH
  $(error no $(PROJECT)_FLASH defined!)
else
# check if flash chip is known
  ifeq (, $(filter $($(PROJECT)_FLASH),$(FLASH_CHIPS)))
    $(error Unknown flash $($(PROJECT)_FLASH) available chips: $(FLASH_CHIPS))
	else
		FLASH := $($(PROJECT)_FLASH)
  endif
endif

