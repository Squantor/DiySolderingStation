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
#include <application.hpp>

class Menu_item_contrast : public Menu_item {
 public:
  Menu_item_contrast() : type(Menu_item_type::value) {}

  [[nodiscard]] Menu_item_type get_type() const noexcept final {
    return type;
  }

  [[nodiscard]] const char *render(std::span<char> buffer) const noexcept final {
    libmcu::Mregel line(buffer);
    line.add("Contrast ");
    line.add(libmcu::Dec(static_cast<std::int32_t>(application::current_settings.contrast)));
    return line.c_str();
  }

  void increment() noexcept final {
    if (application::current_settings.contrast < 240)
      application::current_settings.contrast += 20;
    ui_display.contrast(application::current_settings.contrast);
  }

  void decrement() noexcept final {
    if (application::current_settings.contrast > 0)
      application::current_settings.contrast -= 20;
    ui_display.contrast(application::current_settings.contrast);
  }

  void action() noexcept final {}

 private:
  const Menu_item_type type;
};

#endif