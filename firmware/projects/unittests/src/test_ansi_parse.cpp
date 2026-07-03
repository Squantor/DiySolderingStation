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
#include <minunit.h>
#include <stdint.h>
#include <ansi_parse.hpp>

squLib::ansiParse ansiParseDut;

MINUNIT_SETUP(ansiParseSetup) {
  ansiParseDut.reset();
  MINUNIT_PASS();
}

MINUNIT_SETUP(ansiParseTeardown) {
  MINUNIT_PASS();
}

/**
 * @brief Tests state transitions of the Ansi parser
 */
MINUNIT_ADD(ansiParseStateTests, ansiParseSetup, ansiParseTeardown) {
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input('A') == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input('\e') == squLib::ansiParserState::busy);
  ansiParseDut.reset();
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input('\e') == squLib::ansiParserState::busy);
  MINUNIT_CHECK(ansiParseDut.input('[') == squLib::ansiParserState::busy);
  MINUNIT_CHECK(ansiParseDut.input('A') == squLib::ansiParserState::ready);
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::ready);
  MINUNIT_CHECK(ansiParseDut.getSequence() == squLib::ansiSequence::cursorUp);
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
}

/**
 * @brief Check all ansi squences
 */
MINUNIT_ADD(ansiParseSequences, ansiParseSetup, ansiParseTeardown) {
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input("\e[A") == squLib::ansiParserState::ready);
  MINUNIT_CHECK(ansiParseDut.getSequence() == squLib::ansiSequence::cursorUp);
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input("\e[B") == squLib::ansiParserState::ready);
  MINUNIT_CHECK(ansiParseDut.getSequence() == squLib::ansiSequence::cursorDown);
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input("\e[C") == squLib::ansiParserState::ready);
  MINUNIT_CHECK(ansiParseDut.getSequence() == squLib::ansiSequence::cursorForward);
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
  MINUNIT_CHECK(ansiParseDut.input("\e[D") == squLib::ansiParserState::ready);
  MINUNIT_CHECK(ansiParseDut.getSequence() == squLib::ansiSequence::cursorBackward);
  MINUNIT_CHECK(ansiParseDut.status() == squLib::ansiParserState::idle);
}
