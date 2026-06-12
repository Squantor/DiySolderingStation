/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item.hpp
 * @brief Menu screen item definition
 *
 */
#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <span>

enum class Menu_item_type : std::uint8_t {
  value, /*!< value item */
  exit,  /*!< exit item */
};

class Menu_item {
 public:
  [[nodiscard]] virtual Menu_item_type get_type() const noexcept = 0;

  [[nodiscard]] virtual const char *render(std::span<char> buffer) const noexcept = 0;

  virtual void increment() noexcept = 0;

  virtual void decrement() noexcept = 0;

 private:
};

#endif