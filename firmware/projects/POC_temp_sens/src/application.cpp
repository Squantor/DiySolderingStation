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
void application::init() {
  usartPeripheral.claim();
}
void application::progress() {
  libMcu::results status;
  std::array<std::uint8_t, 10> line;
  usartPeripheral.startRead(line);
  do {
    status = usartPeripheral.progressRead();
  } while (status != libMcu::results::DONE);
  usartPeripheral.startWrite(line);
  do {
    status = usartPeripheral.progressWrite();
  } while (status != libMcu::results::DONE);
}
}  // namespace application
