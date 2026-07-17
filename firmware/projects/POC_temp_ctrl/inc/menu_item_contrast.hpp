/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item_constrast.hpp
 * @brief Menu screen for oled contrast setting
 *
 */
#ifndef MENU_ITEM_CONTRAST_HPP
#define MENU_ITEM_CONTRAST_HPP

#include "menu_item.hpp"
#include <POC_temp_control_nuclone.hpp>

class Menu_item_contrast : public Menu_item {
 public:
  Menu_item_contrast() : type(Menu_item_type::value), value(20) {}

  [[nodiscard]] Menu_item_type get_type() const noexcept final {
    return type;
  }

  [[nodiscard]] const char *render(std::span<char> buffer) const noexcept final {
    libmcu::Mregel line(buffer);
    line.add("Contrast ");
    line.add(libmcu::Dec(static_cast<std::int32_t>(value)));
    return line.c_str();
  }

  void increment() noexcept final {
    if (value < 240)
      value += 20;
    ui_display.contrast(value);
  }

  void decrement() noexcept final {
    if (value > 0)
      value -= 20;
    ui_display.contrast(value);
  }

 private:
  const Menu_item_type type;
  std::uint8_t value;
};

#endif