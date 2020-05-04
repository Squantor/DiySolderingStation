# MIT License

# Copyright (c) 2020 Bart Bilos

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# settings for the MCU target
#
# Version: 20200427

ifndef MCU
$(error MCU is not defined!)
else
include targets/$(MCU).mk
endif

# valid configurations like debug, release, test, define them here
CONFIGS = debug release

# configuration specific flags
CFLAGS += -std=gnu11 -Wall -Wextra -Wno-main -fno-common -c -ffunction-sections -fdata-sections
CFLAGS_debug += -Og -g3
CFLAGS_release += -Os -g
CXXFLAGS += -std=c++17 -Wall -Wextra -Wno-main -fno-common -c -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
CXXFLAGS_debug += -Og -g3
CXXFLAGS_release += -Os -g
ASMFLAGS += -c -x assembler-with-cpp
LDFLAGS +=  -nostdlib -Wl,--gc-sections -Wl,-print-memory-usage
DEFINES += -D$(BOARD)
DEFINES_release += -DNDEBUG
DEFINES_debug += -DDEBUG

