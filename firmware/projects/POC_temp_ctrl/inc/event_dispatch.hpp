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

struct EventHandlerPair {
  EventHandler *handler;
  Events event;
};

class EventDispatcher {
 public:
  EventDispatcher(std::span<const EventHandlerPair> event_handlers) : handlers(event_handlers) {}

  void Reset() {
    queue.Reset();
  }

  std::size_t GetEventCount() {
    return queue.GetLevel();
  }

  void PostEvent(EventData event) {
    queue.PushFront(event);
  }

  /**
   * @brief Processes events that are pending
   */
  void Process() {
    if (queue.GetLevel() > 0) {
      EventData event;
      queue.PopBack(event);
      for (const EventHandlerPair &handler : handlers) {
        if (handler.event == event.event) {
          handler.handler->HandleEvent(event);
        }
      }
    }
  }

 private:
  libmcu::RingBuffer<EventData, 10> queue;
  std::span<const EventHandlerPair> handlers;
};

#endif
