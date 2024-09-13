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
#include <mock_char_device.hpp>

int fooCounter;
int barCounter;
int zagCounter;
int helpCounter;

squLib::results fooFunc(std::span<const char> commandLine) {
  (void)commandLine;
  fooCounter = fooCounter + 1;
  return squLib::results::ok;
}
squLib::results barFunc(std::span<const char> commandLine) {
  (void)commandLine;
  barCounter = barCounter + 1;
  return squLib::results::ok;
}
squLib::results zagFunc(std::span<const char> commandLine) {
  (void)commandLine;
  zagCounter = zagCounter + 1;
  return squLib::results::ok;
}
squLib::results helpFunc(std::span<const char> commandLine);

squLib::commandHandler fooCmdHandle{"foo", "fooing the foo\n", fooFunc};
squLib::commandHandler barCmdHandle{"bar", "barring the bar\n", barFunc};
squLib::commandHandler zagCmdHandle{"zag", "zagging the zag\n", zagFunc};
squLib::commandHandler helpCmdHandle{"help", "Prints available commands\n", helpFunc};

std::array<const squLib::commandHandler, 4> commandHandlerArray{helpCmdHandle, fooCmdHandle, barCmdHandle, zagCmdHandle};
std::span<const squLib::commandHandler> commandHandlers{commandHandlerArray};
static mocks::charDevice<200> charDeviceMock;

squLib::commandInterpreter<commandHandlers, charDeviceMock> commandInterpreterDut;

squLib::results helpFunc(std::span<const char> commandLine) {
  (void)commandLine;
  commandInterpreterDut.printHelp();
  helpCounter = helpCounter + 1;
  return squLib::results::ok;
}

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(commandInterpreterSetup) {
  fooCounter = 0;
  barCounter = 0;
  zagCounter = 0;
  helpCounter = 0;
  charDeviceMock.reset();
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
  std::array<const char, 4> validCmd1{"foo"};
  std::array<const char, 4> validCmd2{"zag"};
  minUnitCheck(commandInterpreterDut.handle(singleChar) == squLib::results::notFound);
  minUnitCheck(commandInterpreterDut.handle(InvalidCmd) == squLib::results::notFound);
  minUnitCheck(fooCounter == 0);
  minUnitCheck(commandInterpreterDut.handle(validCmd1) == squLib::results::ok);
  minUnitCheck(fooCounter == 1);
  minUnitCheck(zagCounter == 0);
  minUnitCheck(commandInterpreterDut.handle(validCmd2) == squLib::results::ok);
  minUnitCheck(zagCounter == 1);
}

/**
 * @brief Check help printing
 */
MINUNIT_ADD(commandInterpreterPrintHelp, commandInterpreterSetup, commandInterpreterTeardown) {
  std::array<const char, 5> helpCmd{"help"};
  minUnitCheck(commandInterpreterDut.handle(helpCmd) == squLib::results::ok);
  minUnitCheck(std::strlen(charDeviceMock.writeBuffer.data()) == 102);
  minUnitCheck(std::strcmp(charDeviceMock.writeBuffer.data(),
                           "help \t: Prints available commands\n"
                           "foo \t: fooing the foo\n"
                           "bar \t: barring the bar\n"
                           "zag \t: zagging the zag\n") == 0);
}
