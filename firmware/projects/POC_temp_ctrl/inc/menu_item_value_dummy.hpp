/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item_value_dummy.hpp
 * @brief Menu screen dummy value item definition
 *
 */
#ifndef MENU_ITEM_VALUE_DUMMY_HPP
#define MENU_ITEM_VALUE_DUMMY_HPP

#include "menu_item.hpp"

class Menu_item_value_dummy : public Menu_item {
 public:
  Menu_item_value_dummy(Menu_item_type menu_item_type, const char *menu_item_name, std::int32_t menu_value)
    : type(menu_item_type), name(menu_item_name), value(menu_value) {}

  [[nodiscard]] Menu_item_type get_type() const noexcept override {
    return type;
  }

  [[nodiscard]] const char *render(std::span<char> buffer) const noexcept override {
    libmcu::Mregel line(buffer);
    line.add(name);
    line.add(' ');
    line.add(libmcu::Dec(value));
    return line.c_str();
  }

  void increment() noexcept override {
    value++;
  }

  void decrement() noexcept override {
    value--;
  }

 private:
  const Menu_item_type type;
  const char *name;
  std::int32_t value;
};

#endif