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
  BoardInit();
  application::Results result = application::controller.Init();
  if (result != application::Results::NoError) {
    application::command_console.print("Failed to initialize application\n");
  }
  while (result == application::Results::NoError) {
    result = application::controller.Progress();
  }
  application::command_console.print("Application mainloop exited with error code %hhu\n", static_cast<std::uint8_t>(result));
  LIBMCULL_BKPT(0x11);
  while (1)
    ;
}
