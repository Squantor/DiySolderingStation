/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file event_dispatch.hpp
 * Event dispatcher definitions
 */
#ifndef EVENT_DISPATCH_HPP
#define EVENT_DISPATCH_HPP

#include "events.hpp"
#include "event_handler.hpp"

struct Event_handler_pair {
  Event_handler *handler;
  Events event;
};

class Event_dispatcher {
 public:
  Event_dispatcher(std::span<const Event_handler_pair> event_handlers) : handlers(event_handlers) {}

  void reset() {
    queue.reset();
  }

  std::size_t get_event_count() {
    return queue.get_level();
  }

  void post_event(Event_data event) {
    queue.push_front(event);
  }

  /**
   * @brief Processes events that are pending
   */
  void process() {
    if (queue.get_level() > 0) {
      Event_data event;
      queue.pop_back(event);
      for (const Event_handler_pair &handler : handlers) {
        if (handler.event == event.event) {
          handler.handler->handle_event(event);
        }
      }
    }
  }

 private:
  libmcu::Ring_buffer<Event_data, 10> queue;
  std::span<const Event_handler_pair> handlers;
};

#endif
