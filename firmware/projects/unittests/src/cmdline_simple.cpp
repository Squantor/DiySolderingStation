/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_cmdline_simple.cpp
 * All tests for testing the simple commandline parser class
 */
#include <minunit.h>
#include <stdint.h>
#include <console.hpp>
#include <mock_char_device.hpp>
#include <cmdline_simple.hpp>
#include <cstring>

namespace mocks {
class commandHandle {
 public:
  commandHandle() : commandSize{0} {}
  void reset() {
    commandSize = 0;
  }
  squLib::results handle(std::span<const char> input) {
    for (const char &element : input) {
      command[commandSize] = element;
      commandSize = commandSize + 1;
    }
    return squLib::results::ok;
  }

  std::array<char, 32> command;
  std::size_t commandSize;
};
}  // namespace mocks

static mocks::commandHandle commandHandleMock;
static mocks::charDevice<42> charDeviceMock;
static squLib::commandlineSimple<6, charDeviceMock, commandHandleMock> dutCommandlineSimple;

MINUNIT_SETUP(cmdlineSimpleSetup) {
  dutCommandlineSimple.reset();
  charDeviceMock.reset();
  commandHandleMock.commandSize = 0;
  MINUNIT_PASS();
}

MINUNIT_SETUP(cmdlineSimpleTeardown) {
  MINUNIT_PASS();
}

/**
 * @brief write single one letter command
 */
MINUNIT_ADD(testSingleCommand, cmdlineSimpleSetup, cmdlineSimpleTeardown) {
  std::array<char, 1> singleChar;
  singleChar[0] = 'F';
  dutCommandlineSimple.input(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 1);
  MINUNIT_CHECK(commandHandleMock.commandSize == 0);
  singleChar[0] = '\n';
  dutCommandlineSimple.input(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 2);
  MINUNIT_CHECK(commandHandleMock.commandSize == 1);
  MINUNIT_CHECK(std::memcmp(commandHandleMock.command.data(), "F", 1) == 0);
}

/**
 * @brief test backspace handling
 */
MINUNIT_ADD(testBackspaceHandling, cmdlineSimpleSetup, cmdlineSimpleTeardown) {
  std::array<char, 7> testString{"F\bC\bG\n"};
  dutCommandlineSimple.input(std::span<char>(testString).first(6));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 10);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "F\b \bC\b \bG\n", 10) == 0);
  MINUNIT_CHECK(commandHandleMock.commandSize == 1);
  MINUNIT_CHECK(std::memcmp(commandHandleMock.command.data(), "G", 1) == 0);
}

// TODO ANSI up and down handling (previous and clear command)
// TODO ANSI cursor movement handling (inserting and deleting characters)
