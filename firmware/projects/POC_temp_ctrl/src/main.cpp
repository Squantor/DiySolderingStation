/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for Diy Solder
 */
#include <POC_temp_control_nuclone.hpp>
#include <application.hpp>

namespace application {
Application controller;
}

int main() {
  board_init();
  Results result = application::controller.init();
  if (result != Results::no_error) {
    application::command_console.print("Failed to initialize application\n");
  }
  while (result == Results::no_error) {
    board_progress();
    result = application::controller.progress();
  }
  application::command_console.print("Application mainloop exited with error code %hhu\n", static_cast<std::uint8_t>(result));
  LIBMCULL_BKPT(0x11);
  while (1)
    ;
}
