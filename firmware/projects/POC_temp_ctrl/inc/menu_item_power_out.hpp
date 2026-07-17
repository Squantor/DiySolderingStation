/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item_power_out.hpp
 * @brief Menu item for solder iron power output setting
 *
 */
#ifndef MENU_ITEM_POWER_OUT_HPP
#define MENU_ITEM_POWER_OUT_HPP

#include "menu_item.hpp"
#include <application.hpp>

class Menu_item_power_out : public Menu_item {
 public:
  Menu_item_power_out(std::size_t index) : type(Menu_item_type::value), iron_index(index), value(50) {}

  [[nodiscard]] Menu_item_type get_type() const noexcept final {
    return type;
  }

  [[nodiscard]] const char *render(std::span<char> buffer) const noexcept final {
    libmcu::Mregel line(buffer);
    line.add("Iron ");
    line.add(libmcu::Dec(static_cast<std::int32_t>(iron_index)));
    line.add(" Power ");
    line.add(libmcu::Dec(static_cast<std::int32_t>(value)));
    return line.c_str();
  }

  void increment() noexcept final {
    if (value < 100)
      value += 10;
    application::solder_iron_controller.set_power(iron_index, value);
  }

  void decrement() noexcept final {
    if (value > 0)
      value -= 10;
    application::solder_iron_controller.set_power(iron_index, value);
  }

 private:
  const Menu_item_type type;
  std::size_t iron_index;
  std::uint8_t value;
};

#endif