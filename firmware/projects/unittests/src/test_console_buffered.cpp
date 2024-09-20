/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file Tests for character based console driver
 */
#include <MinUnit.h>
#include <console_buffered.hpp>
#include <mock_char_device.hpp>
#include <cstring>

static mocks::charDevice<42> charDeviceMock;
static squLib::console<charDeviceMock, 20> dutConsoleBuffered;

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(consoleBufferedSetup) {
  charDeviceMock.readIndex = 0;
  charDeviceMock.writeIndex = 0;
  dutConsoleBuffered.reset();
  minUnitPass();
}

/**
 * @brief teardown and cleanup
 */
MINUNIT_TEARDOWN(consoleBufferedTeardown) {
  minUnitPass();
}

/**
 * @brief Test console write functionality
 */
MINUNIT_ADD(consoleWriteTest, consoleBufferedSetup, consoleBufferedTeardown) {
  std::array<char, 1> singleChar;
  std::array<char, 8> testString{"Gazonk\n"};
  singleChar[0] = 'F';
  dutConsoleBuffered.write(singleChar);
  minUnitCheck(charDeviceMock.writeIndex == 0);
  singleChar[0] = '\n';
  dutConsoleBuffered.write(singleChar);
  minUnitCheck(charDeviceMock.writeIndex == 2);
  minUnitCheck(std::memcmp(charDeviceMock.writeBuffer.data(), "F\n", 2) == 0);
  charDeviceMock.writeIndex = 0;
  dutConsoleBuffered.write(std::span<char>(testString).first(3u));
  dutConsoleBuffered.write(std::span<char>(testString).first(6u));
  minUnitCheck(charDeviceMock.writeIndex == 0);
  dutConsoleBuffered.write(std::span<char>(testString).first(7u));
  minUnitCheck(charDeviceMock.writeIndex == 16);
  minUnitCheck(std::memcmp(charDeviceMock.writeBuffer.data(), "GazGazonkGazonk\n", 16) == 0);
}

/**
 * @brief Test console read functionality
 */
MINUNIT_ADD(consoleReadTest, consoleBufferedSetup, consoleBufferedTeardown) {
  std::array<char, 1> singleChar;
  std::array<char, 7> testString;
  memcpy(charDeviceMock.readBuffer.data(), "Gazonk\n", 7);
  dutConsoleBuffered.read(singleChar);
  minUnitCheck(singleChar[0] == 'G');
  minUnitCheck(charDeviceMock.readIndex == 1);
  dutConsoleBuffered.read(singleChar);
  minUnitCheck(singleChar[0] == 'a');
  minUnitCheck(charDeviceMock.readIndex == 2);
  dutConsoleBuffered.read(std::span<char>(testString).first(3));
  minUnitCheck(std::memcmp(testString.data(), "zon", 3) == 0);
  minUnitCheck(charDeviceMock.readIndex == 5);
  charDeviceMock.readIndex = 0;
  dutConsoleBuffered.read(testString);
  minUnitCheck(charDeviceMock.readIndex == 7);
  minUnitCheck(std::memcmp(testString.data(), "Gazonk\n", 7) == 0);
}

/**
 * @brief Test console write overflow functionality
 */
MINUNIT_ADD(consoleWriteTestOverflow, consoleBufferedSetup, consoleBufferedTeardown) {
  std::array<char, 6> testString{"Frobs"};
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  minUnitCheck(charDeviceMock.writeIndex == 0);
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  minUnitCheck(charDeviceMock.writeIndex == 20);
  minUnitCheck(std::memcmp(charDeviceMock.writeBuffer.data(), "FrobsFrobsFrobsFrobs", 20) == 0);
}