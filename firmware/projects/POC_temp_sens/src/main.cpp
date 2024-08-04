/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for Diy Solder
 */
#include <POC_temp_sense_nuclone.hpp>
#include <application.hpp>

application::application controller;

int main() {
  boardInit();
  controller.init();
  while (1) {
    controller.progress();
  }
}
