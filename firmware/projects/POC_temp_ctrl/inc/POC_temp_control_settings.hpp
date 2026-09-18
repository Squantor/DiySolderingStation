/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file POC_temp_control_settings.hpp
 * @brief POC_temp_control settings structure
 */
#ifndef POC_TEMP_CONTROL_SETTINGS_HPP
#define POC_TEMP_CONTROL_SETTINGS_HPP

#include <cstdint>

namespace application {

struct POC_temp_control_settings {
  std::uint8_t contrast;  //! OLED display contrast value
};

}  // namespace application

#endif