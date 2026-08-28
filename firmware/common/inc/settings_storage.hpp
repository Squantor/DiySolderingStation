/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file settings_storage.hpp
 * @brief Settings storage class definitions
 */
#ifndef SETTINGS_STORAGE_HPP
#define SETTINGS_STORAGE_HPP

#include <cstdint>

namespace detail {
/**
 * @brief Settings storage record
 * @tparam Application_settings
 */
template <typename Application_settings>
struct Settings_storage_record {
  uint8_t sequence_number;        //! Sequence number
  uint8_t version;                //! Version of settings structure, will ignore mismatches
  uint16_t checksum;              //! checksum, simple 8 bit add is used for now
  Application_settings settings;  //! Application settings
};
}  // namespace detail

/**
 * @brief Settings storage class
 * @tparam Application_settings structure to use for settings storage
 * @todo pass EEPROM class to settings storage
 */
template <typename Application_settings>
struct Settings_storage : public libmcu::NonBlocking {
  /**
   * @brief Construct and initialize a new settings_storage object
   */
  Settings_storage() {}
  /**
   * @brief Initialize the settings storage
   * Goes through EEPROM and loads latest settings or defaults
   * @todo parameters definition for settings store and defaults
   */
  void init(Application_settings settings, Application_settings defaults) {}
  /**
   * @brief Save the settings passed on to the storage
   *
   */
  void save() {}

 private:
  //! @todo some kind of state variable if it is busy? Yes, is a async class
};

#endif