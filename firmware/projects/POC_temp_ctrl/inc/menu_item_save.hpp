/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item_save.hpp
 * @brief Menu screen save item definition
 *
 */
#ifndef MENU_ITEM_SAVE_HPP
#define MENU_ITEM_SAVE_HPP

#include <libmcu/data_struct/mregel.hpp>
#include <span>
#include "menu_item.hpp"

class Menu_item_save : public Menu_item {
 public:
  Menu_item_type get_type() const noexcept final {
    return Menu_item_type::action;
  }
  const char *render(std::span<char>) const noexcept final {
    return "Save";
  }

  void increment() noexcept final {}
  void decrement() noexcept final {}
  void action() noexcept final {
    application::write_current_settings();
  }

 private:
};

#endif