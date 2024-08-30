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

squLib::ansiParse ansiParseDut;

MINUNIT_SETUP(ansiParseSetup) {
  ansiParseDut.reset();
  minUnitPass();
}

MINUNIT_SETUP(ansiParseTeardown) {
  minUnitPass();
}

/**
 * @brief Tests state transitions of the Ansi parser
 */
MINUNIT_ADD(ansiParseStateTests, ansiParseSetup, ansiParseTeardown) {
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input('A') == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input('\e') == squLib::ansiParserState::busy);
  ansiParseDut.reset();
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input('\e') == squLib::ansiParserState::busy);
  minUnitCheck(ansiParseDut.input('[') == squLib::ansiParserState::busy);
  minUnitCheck(ansiParseDut.input('A') == squLib::ansiParserState::ready);
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::ready);
  minUnitCheck(ansiParseDut.getSequence() == squLib::ansiSequence::cursorUp);
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
}

/**
 * @brief Check all ansi squences
 */
MINUNIT_ADD(ansiParseSequences, ansiParseSetup, ansiParseTeardown) {
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input("\e[A") == squLib::ansiParserState::ready);
  minUnitCheck(ansiParseDut.getSequence() == squLib::ansiSequence::cursorUp);
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input("\e[B") == squLib::ansiParserState::ready);
  minUnitCheck(ansiParseDut.getSequence() == squLib::ansiSequence::cursorDown);
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input("\e[C") == squLib::ansiParserState::ready);
  minUnitCheck(ansiParseDut.getSequence() == squLib::ansiSequence::cursorForward);
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
  minUnitCheck(ansiParseDut.input("\e[D") == squLib::ansiParserState::ready);
  minUnitCheck(ansiParseDut.getSequence() == squLib::ansiSequence::cursorBackward);
  minUnitCheck(ansiParseDut.status() == squLib::ansiParserState::idle);
}
