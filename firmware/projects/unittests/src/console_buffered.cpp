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
  MINUNIT_PASS();
}

/**
 * @brief teardown and cleanup
 */
MINUNIT_TEARDOWN(consoleBufferedTeardown) {
  MINUNIT_PASS();
}

/**
 * @brief Test console write functionality
 */
MINUNIT_ADD(consoleWriteTest, consoleBufferedSetup, consoleBufferedTeardown) {
  std::array<char, 1> singleChar;
  std::array<char, 8> testString{"Gazonk\n"};
  singleChar[0] = 'F';
  dutConsoleBuffered.write(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 0);
  singleChar[0] = '\n';
  dutConsoleBuffered.write(singleChar);
  MINUNIT_CHECK(charDeviceMock.writeIndex == 2);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "F\n", 2) == 0);
  charDeviceMock.writeIndex = 0;
  dutConsoleBuffered.write(std::span<char>(testString).first(3u));
  dutConsoleBuffered.write(std::span<char>(testString).first(6u));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 0);
  dutConsoleBuffered.write(std::span<char>(testString).first(7u));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 16);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "GazGazonkGazonk\n", 16) == 0);
}

/**
 * @brief Test console read functionality
 */
MINUNIT_ADD(consoleReadTest, consoleBufferedSetup, consoleBufferedTeardown) {
  std::array<char, 1> singleChar;
  std::array<char, 7> testString;
  memcpy(charDeviceMock.readBuffer.data(), "Gazonk\n", 7);
  dutConsoleBuffered.read(singleChar);
  MINUNIT_CHECK(singleChar[0] == 'G');
  MINUNIT_CHECK(charDeviceMock.readIndex == 1);
  dutConsoleBuffered.read(singleChar);
  MINUNIT_CHECK(singleChar[0] == 'a');
  MINUNIT_CHECK(charDeviceMock.readIndex == 2);
  dutConsoleBuffered.read(std::span<char>(testString).first(3));
  MINUNIT_CHECK(std::memcmp(testString.data(), "zon", 3) == 0);
  MINUNIT_CHECK(charDeviceMock.readIndex == 5);
  charDeviceMock.readIndex = 0;
  dutConsoleBuffered.read(testString);
  MINUNIT_CHECK(charDeviceMock.readIndex == 7);
  MINUNIT_CHECK(std::memcmp(testString.data(), "Gazonk\n", 7) == 0);
}

/**
 * @brief Test console write overflow functionality
 */
MINUNIT_ADD(consoleWriteTestOverflow, consoleBufferedSetup, consoleBufferedTeardown) {
  std::array<char, 6> testString{"Frobs"};
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 0);
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  dutConsoleBuffered.write(std::span<char>(testString).first(5));
  MINUNIT_CHECK(charDeviceMock.writeIndex == 20);
  MINUNIT_CHECK(std::memcmp(charDeviceMock.writeBuffer.data(), "FrobsFrobsFrobsFrobs", 20) == 0);
}