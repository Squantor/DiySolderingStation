/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_parse_ansi.cpp
 * All tests for testing the ansi parser
 */
#include <MinUnit.h>
#include <stdint.h>
#include <ansi_parse.hpp>

squLib::ansiParse classUnderTest;

MINUNIT_SETUP(ansiParseSetup) {
  classUnderTest.reset();
  minUnitPass();
}

MINUNIT_SETUP(ansiParseTeardown) {
  minUnitPass();
}

/**
 * @brief Tests state transitions of the Ansi parser
 */
MINUNIT_ADD(ansiParseStateTests, ansiParseSetup, ansiParseTeardown) {
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input('A') == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input('\e') == squLib::ansiParserState::busy);
  classUnderTest.reset();
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input('\e') == squLib::ansiParserState::busy);
  minUnitCheck(classUnderTest.input('[') == squLib::ansiParserState::busy);
  minUnitCheck(classUnderTest.input('A') == squLib::ansiParserState::ready);
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::ready);
  minUnitCheck(classUnderTest.getSequence() == squLib::ansiSequence::cursorUp);
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
}

/**
 * @brief Check all ansi squences
 */
MINUNIT_ADD(ansiParseSequences, ansiParseSetup, ansiParseTeardown) {
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input("\e[A") == squLib::ansiParserState::ready);
  minUnitCheck(classUnderTest.getSequence() == squLib::ansiSequence::cursorUp);
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input("\e[B") == squLib::ansiParserState::ready);
  minUnitCheck(classUnderTest.getSequence() == squLib::ansiSequence::cursorDown);
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input("\e[C") == squLib::ansiParserState::ready);
  minUnitCheck(classUnderTest.getSequence() == squLib::ansiSequence::cursorForward);
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
  minUnitCheck(classUnderTest.input("\e[D") == squLib::ansiParserState::ready);
  minUnitCheck(classUnderTest.getSequence() == squLib::ansiSequence::cursorBackward);
  minUnitCheck(classUnderTest.status() == squLib::ansiParserState::idle);
}
