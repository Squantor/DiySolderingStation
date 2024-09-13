/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file test template
 */
#include <MinUnit.h>
#include <command_interpreter.hpp>

int fooCounter;
int barCounter;
int zagCounter;

squLib::result fooFunc(std::span<const char> commandLine) {
  (void)commandLine;
  fooCounter = fooCounter + 1;
  return squLib::result::ok;
}
squLib::result barFunc(std::span<const char> commandLine) {
  (void)commandLine;
  barCounter = barCounter + 1;
  return squLib::result::ok;
}
squLib::result zagFunc(std::span<const char> commandLine) {
  (void)commandLine;
  zagCounter = zagCounter + 1;
  return squLib::result::ok;
}

squLib::commandHandler fooCmdHandle{"foo", "fooing the foo", fooFunc};
squLib::commandHandler barCmdHandle{"bar", "barring the bar", barFunc};
squLib::commandHandler zagCmdHandle{"zag", "zagging the zag", zagFunc};

std::array<const squLib::commandHandler, 3> commandHandlerArray{fooCmdHandle, barCmdHandle, zagCmdHandle};
std::span<const squLib::commandHandler> commandHandlers{commandHandlerArray};

squLib::commandInterpreter<commandHandlers> commandInterpreterDut;

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(commandInterpreterSetup) {
  fooCounter = 0;
  barCounter = 0;
  zagCounter = 0;
  minUnitPass();
}

/**
 * @brief Teardown
 */
MINUNIT_TEARDOWN(commandInterpreterTeardown) {
  minUnitPass();
}

/**
 * @brief Various not found conditions
 */
MINUNIT_ADD(commandInterpreterCommandParse, commandInterpreterSetup, commandInterpreterTeardown) {
  std::array<const char, 2> singleChar{"b"};
  std::array<const char, 6> InvalidCmd{"blorp"};
  std::array<const char, 4> validCmd{"foo"};
  minUnitCheck(commandInterpreterDut.handle(singleChar) == squLib::result::notFound);
  minUnitCheck(commandInterpreterDut.handle(InvalidCmd) == squLib::result::notFound);
  minUnitCheck(fooCounter == 0);
  minUnitCheck(commandInterpreterDut.handle(validCmd) == squLib::result::ok);
  minUnitCheck(fooCounter == 1);
}
