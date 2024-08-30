/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief ANSI sequence parser
 */
#ifndef ANSI_PARSE_HPP
#define ANSI_PARSE_HPP
namespace squLib {

enum class ansiParserState {
  idle,  /**< Idle */
  busy,  /**< We are busy parsing something */
  ready, /**< Sequence parsed, ready to be read out */
  error, /**< Some kind of error during parsing */
};

enum class ansiSequence {
  none,           /**< No squence parsed */
  cursorUp,       /**< Move cursor one up */
  cursorDown,     /**< Move cursor one down */
  cursorForward,  /**< Move cursor one forward */
  cursorBackward, /**< Move cursor one backward */
};

namespace detail {
enum class ansiParserState {
  idle,    /**< Idle */
  entered, /**< We have entered an ANSI squence */
  bracket, /**< Our ansi squence entered a bracket */
  ready,   /**< Sequence parsed, ready to be read out */
  error,   /**< Some kind of error during parsing */
};
}  // namespace detail

class ansiParse {
 public:
  ansiParse() : state{detail::ansiParserState::idle} {}
  /**
   * @brief Reset ansi parser state
   */
  void reset() {
    state = detail::ansiParserState::idle;
    sequence = ansiSequence::none;
  }
  /**
   * @brief Returns current parser state
   * @return ansiParserState
   */
  ansiParserState status() {
    switch (state) {
      case detail::ansiParserState::idle:
        return ansiParserState::idle;
      case detail::ansiParserState::entered:
        return ansiParserState::busy;
      case detail::ansiParserState::bracket:
        return ansiParserState::busy;
      case detail::ansiParserState::ready:
        return ansiParserState::ready;
      case detail::ansiParserState::error:
        return ansiParserState::error;
    }
    return ansiParserState::error;
  }

  /**
   * @brief Inputs character for the ANSI parser
   * @param c character to input
   * @return state the parser is in
   */
  ansiParserState inputChar(char c);

  /**
   * @brief Get the parsed squence, no checking on intermediate state
   * Resets internal state automatically
   * @return parsed ansi squence
   */
  ansiSequence getSequence() {
    ansiSequence returnValue = sequence;
    state = detail::ansiParserState::idle;
    sequence = ansiSequence::none;
    return returnValue;
  }

 private:
  detail::ansiParserState state;
  ansiSequence sequence;
};
}  // namespace squLib
#endif