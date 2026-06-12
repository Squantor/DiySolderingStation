/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item_exit.hpp
 * @brief Menu screen exit item definition
 *
 */
#ifndef MENU_ITEM_EXIT_HPP
#define MENU_ITEM_EXIT_HPP

#include <libmcu/data_struct/mregel.hpp>
#include <span>
#include "menu_item.hpp"

class Menu_item_exit : public Menu_item {
 public:
  Menu_item_type get_type() const noexcept override {
    return Menu_item_type::exit;
  }
  const char *render(std::span<char>) const noexcept override {
    return "Exit";
  }

  void increment() noexcept override final {}
  void decrement() noexcept override final {}

 private:
};

#endif