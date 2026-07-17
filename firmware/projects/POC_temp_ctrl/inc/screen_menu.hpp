/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file screen_menu.hpp
 * @brief Menu screen definition
 *
 */
#ifndef SCREEN_MENU_HPP
#define SCREEN_MENU_HPP

#include "event_handler.hpp"
#include "user_interface_events.hpp"
#include "user_interface.hpp"
#include "mid/gfx_display.hpp"
#include "application_font.hpp"
#include "POC_temp_control_nuclone.hpp"
#include "menu_item.hpp"

namespace detail {
enum class Menu_screen_state : std::uint8_t {
  inactive,  /*<! inactive state */
  active,    /*!< active state */
  selecting, /*!< Selecting menu item */
  entered,   /*!< Entered menu item */
};
}  // namespace detail

/**
 * @brief Menu screen
 * @tparam &display
 */
template <auto &display>
class Menu_screen : public User_interface_screen<User_interface_events>, public Event_handler {
 public:
  Menu_screen(std::span<Menu_item *const> menu_items) : state(detail::Menu_screen_state::inactive), items(menu_items) {}

  User_interface_actions handle_event(User_interface_events event) final {
    User_interface_actions action = User_interface_actions::none;

    switch (event) {
      case User_interface_events::enter_button_pressed:
        if (state == detail::Menu_screen_state::active) {
          state = detail::Menu_screen_state::selecting;
        } else if (state == detail::Menu_screen_state::selecting) {
          if (items[item_index]->get_type() == Menu_item_type::exit) {
            state = detail::Menu_screen_state::active;
          } else {
            state = detail::Menu_screen_state::entered;
          }
        } else if (state == detail::Menu_screen_state::entered) {
          state = detail::Menu_screen_state::selecting;
        }
        break;
      case User_interface_events::left_button_pressed:
        if (state == detail::Menu_screen_state::active) {
          action = User_interface_actions::previous_screen;
        } else if (state == detail::Menu_screen_state::selecting) {
          if (item_index > 0) {
            item_index--;
          } else {
            item_index = items.size() - 1;
          }
        } else if (state == detail::Menu_screen_state::entered) {
          items[item_index]->decrement();
        }
        break;
      case User_interface_events::right_button_pressed:
        if (state == detail::Menu_screen_state::active) {
          action = User_interface_actions::next_screen;
        } else if (state == detail::Menu_screen_state::selecting) {
          if (item_index < items.size() - 1) {
            item_index++;
          } else {
            item_index = 0;
          }
        } else if (state == detail::Menu_screen_state::entered) {
          items[item_index]->increment();
        }
        break;
      default:
        break;
    }

    render();
    return action;
  }
  void activate() final {
    state = detail::Menu_screen_state::active;
    item_index = 0;
    render();
  }
  void deactivate() final {
    state = detail::Menu_screen_state::inactive;
  }
  void handle_event(Event_data event) {
    switch (event.event) {
      case Events::seconds:

        break;

      default:
        break;
    }
    render();
  }

 private:
  void render() {
    std::array<char, 16> menu_item_buffer;
    if (state != detail::Menu_screen_state::inactive) {
      display.clear();
      if (state == detail::Menu_screen_state::selecting || state == detail::Menu_screen_state::entered) {
        for (size_t i = 0; i < items.size(); i++) {
          if (i == item_index) {
            display.print(items[i]->render(menu_item_buffer), application_font, libmcu::bitmap::Blit_ops::INVERT);
          } else {
            display.print(items[i]->render(menu_item_buffer), application_font);
          }
          display.print("\n", application_font);
        }

      } else {
        for (auto &item : items) {
          display.print(item->render(menu_item_buffer), application_font);
          display.print("\n", application_font);
        }
      }
      display.flip();
    }
  }
  detail::Menu_screen_state state;
  std::size_t item_index;
  std::span<Menu_item *const> items;
};

#endif