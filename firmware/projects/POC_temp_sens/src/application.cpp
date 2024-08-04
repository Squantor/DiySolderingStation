/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */
#include <POC_temp_sense_nuclone.hpp>
#include <application.hpp>

namespace application {
void application::progress() {
  std::uint32_t firstCount = systickPeripheral.getCount();
}
}  // namespace application
