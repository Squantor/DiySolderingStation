/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief ANSI sequence parser
 */
#include <ansi_parse.hpp>

namespace squLib {
ansiParserState ansiParse::inputChar(char c) {
  if ((c == '\e') && (state == detail::ansiParserState::idle)) {
    state = detail::ansiParserState::entered;
  } else if (state == detail::ansiParserState::entered) {
    switch (c) {
      case '[':
        state = detail::ansiParserState::bracket;
        break;
      default:
        state = detail::ansiParserState::error;
        break;
    }
  } else if (state == detail::ansiParserState::bracket) {
    switch (c) {
      case 'A':
        sequence = ansiSequence::cursorUp;
        state = detail::ansiParserState::ready;
        break;
      case 'B':
        sequence = ansiSequence::cursorDown;
        state = detail::ansiParserState::ready;
        break;
      case 'C':
        sequence = ansiSequence::cursorForward;
        state = detail::ansiParserState::ready;
        break;
      case 'D':
        sequence = ansiSequence::cursorBackward;
        state = detail::ansiParserState::ready;
        break;
      default:
        state = detail::ansiParserState::error;
        break;
    }
  }
  return status();
}

}  // namespace squLib
