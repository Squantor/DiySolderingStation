/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file Tests for character based console driver
 */
#include <minunit.h>
#include <console.hpp>
#include <mock_char_device.hpp>
#include <cstring>

static mocks::charDevice<42> charDeviceMock;
static squLib::console<charDeviceMock> dutConsole;

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(consoleSetup) {
  charDeviceMock.readIndex = 0;
  charDeviceMock.writeIndex = 0;
  dutConsole.reset();
  MINUNIT_PASS();
}

/**
 * @brief teardown and cleanup
 */
MINUNIT_TEARDOWN(consoleTeardown) {
  MINUNIT_PASS();
}

/**
 * @brief Test console write functionality
 */
MINUNIT_ADD(consoleWriteTest, consoleSetup, consoleTeardown) {
  std::array<char, 1> singleChar;
  std::array<char, 8> testString{"Gazonk\n"};
  singleChar[0] = 'F';
  dutConsole.Transmit(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 1);
  singleChar[0] = '\n';
  dutConsole.Transmit(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 2);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "F\n", 2) == 0);
  charDeviceMock.reset();
  dutConsole.Transmit(std::span<char>(testString).first(3u));
  dutConsole.Transmit(std::span<char>(testString).first(6u));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 9);
  dutConsole.Transmit(std::span<char>(testString).first(7u));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 16);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "GazGazonkGazonk\n", 16) == 0);
}

/**
 * @brief Test console read functionality
 */
MINUNIT_ADD(consoleReadTest, consoleSetup, consoleTeardown) {
  std::array<char, 1> singleChar;
  std::array<char, 7> testString;
  memcpy(charDeviceMock.readBuffer.data(), "Gazonk\n", 7);
  dutConsole.Receive(singleChar);
  MINUNIT_CHECK(singleChar[0] == 'G');
  MINUNIT_CHECK(charDeviceMock.readIndex == 1);
  dutConsole.Receive(singleChar);
  MINUNIT_CHECK(singleChar[0] == 'a');
  MINUNIT_CHECK(charDeviceMock.readIndex == 2);
  dutConsole.Receive(std::span<char>(testString).first(3));
  MINUNIT_CHECK(std::memcmp(testString.data(), "zon", 3) == 0);
  MINUNIT_CHECK(charDeviceMock.readIndex == 5);
  charDeviceMock.readIndex = 0;
  dutConsole.Receive(testString);
  MINUNIT_CHECK(charDeviceMock.readIndex == 7);
  MINUNIT_CHECK(std::memcmp(testString.data(), "Gazonk\n", 7) == 0);
}

/**
 * @brief Test console character and string print functionality
 */
MINUNIT_ADD(consolePrintCharString, consoleSetup, consoleTeardown) {
  squLib::Chr singleChar{0};
  singleChar.c = 'F';
  dutConsole.print(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 1);
  singleChar.c = '\n';
  dutConsole.print(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 2);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "F\n", 2) == 0);
  charDeviceMock.reset();
  dutConsole.print("blub");
  dutConsole.print("florp");
  MINUNIT_CHECK(charDeviceMock.writeIndex == 9);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "blubflorp", 9) == 0);
}

/**
 * @brief Test console character span printing functionality
 */
MINUNIT_ADD(consolePrintSpan, consoleSetup, consoleTeardown) {
  std::array<char, 8> testString{"Gazonk\n"};
  dutConsole.print(std::span<char>(testString).first(3u));
  dutConsole.print(std::span<char>(testString).first(6u));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 9);
  dutConsole.print(std::span<char>(testString).first(7u));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 16);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "GazGazonkGazonk\n", 16) == 0);
}

/**
 * @brief Test console uint32_t printing functionality
 */
MINUNIT_ADD(consolePrintUint32, consoleSetup, consoleTeardown) {
  std::uint32_t value = 0;
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 1);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "0", 1) == 0);
  charDeviceMock.reset();
  value = 1234;
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 4);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "1234", 4) == 0);
}

/**
 * @brief Test console hex printing functionality
 */
MINUNIT_ADD(consolePrintHex, consoleSetup, consoleTeardown) {
  squLib::Hex value{0};
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 1);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "0", 1) == 0);
  charDeviceMock.reset();
  value.v = 0x1234;
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 4);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "1234", 4) == 0);
  charDeviceMock.reset();
  value.v = 0x89AB;
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 4);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "89ab", 4) == 0);
}

/**
 * @brief Test console decimal printing functionality
 */
MINUNIT_ADD(consolePrintDec, consoleSetup, consoleTeardown) {
  squLib::Dec value{0};
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 1);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "0", 1) == 0);
  charDeviceMock.reset();
  value.v = 1234;
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 4);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "1234", 4) == 0);
  charDeviceMock.reset();
  value.v = -5678;
  dutConsole.print(value);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 5);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "-5678", 5) == 0);
}