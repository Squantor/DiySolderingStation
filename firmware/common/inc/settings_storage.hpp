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
#include <libmcu/libmcu.hpp>

namespace detail {
/**
 * @brief Settings storage record
 * @tparam Application_settings
 */
template <typename Application_settings>
struct Settings_storage_record {
  uint8_t magic_version;          //! signature also used as version
  uint8_t sequence_number;        //! Sequence number
  uint16_t checksum;              //! checksum, simple 8 bit add is used for now
  Application_settings settings;  //! Application settings
};
}  // namespace detail

/**
 * @brief Settings storage class
 * @tparam Application_settings structure to use for settings storage
 * @todo pass EEPROM class to settings storage
 */
template <typename Application_settings, auto &storage_driver>
struct Settings_storage : public libmcu::NonBlocking {
  /**
   * @brief Construct and initialize a new settings_storage object
   * @todo add buffer for writing to storage driver
   */
  Settings_storage(std::span<std::uint8_t> storage_buffer, std::uint8_t magic_version)
    : state{libmcu::States::Uninitialized},
      storage_buffer{storage_buffer},
      magic_version{magic_version},
      current_address{storage_driver.size()},
      search_address{0},
      sequence_number{0} {}
  /**
   * @brief Get current state
   * @return Current state
   */
  libmcu::States get_state() {
    return state;
  }
  /**
   * @brief Initialize the settings storage
   * @param settings Settings to initialize
   * @param defaults Default settings
   */
  void init(Application_settings &settings, Application_settings &defaults) {
    settings_store = &settings;
    defaults_store = &defaults;
    state = libmcu::States::Initializing;
    storage_driver.read(search_address, storage_buffer, this);
  }
  /**
   * @brief Deinitialize the settings storage
   */
  void deinit() {
    state = libmcu::States::Uninitialized;
    current_address = storage_driver.size();
    search_address = 0;
    sequence_number = 0;
  }
  /**
   * @brief Save the settings passed on to the storage
   * @param settings Settings to save
   */
  void save(Application_settings settings) {}
  /**
   * @brief Progress processing of any operation
   */
  void progress() final {
    switch (state) {
      case libmcu::States::Initializing:
        break;

      default:
        break;
    }
  }
  /**
   * @brief Callback used by driver to notify completion
   * @param result Callback result
   */
  void callback(libmcu::Results result) final {
    (void)result;
    switch (state) {
      case libmcu::States::Initializing:
        if (result == libmcu::Results::NoError) {
          detail::Settings_storage_record<Application_settings> *record =
            reinterpret_cast<detail::Settings_storage_record<Application_settings> *>(storage_buffer.data());

          // analyze record
          if (record->magic_version == magic_version) {
            // check checksum
            // check sequence number, check also for wrapping
            // if all is fine, write to current address
            current_address = search_address;
          }

          // go to next page
          search_address += storage_driver.page_size();
          if (search_address >= storage_driver.size()) {
            // did we find something?
            if (current_address != storage_driver.size()) {
              // We did, read from recorded address
              storage_driver.read(current_address, storage_buffer, this);
              state = libmcu::States::busy_reading;
            } else {
              // We did not, write default settings at address 0
              current_address = 0;
              for (auto &element : storage_buffer) {
                element = 0;
              }
              record->magic_version = magic_version;
              record->sequence_number = 0;
              record->checksum = 0;
              record->settings = *defaults_store;
              storage_driver.write(current_address, storage_buffer, this);
              *settings_store = *defaults_store;
              state = libmcu::States::busy_writing;
            }
          } else {
            storage_driver.read(search_address, storage_buffer, this);
          }
        } else {
          state = libmcu::States::ErrorFatal;
        }
        break;
      case libmcu::States::busy_writing:
        if (result == libmcu::Results::NoError) {
          state = libmcu::States::Idle;
        }
        break;
      case libmcu::States::busy_reading:
        if (result == libmcu::Results::NoError) {
          detail::Settings_storage_record<Application_settings> *record =
            reinterpret_cast<detail::Settings_storage_record<Application_settings> *>(storage_buffer.data());
          *settings_store = record->settings;
          state = libmcu::States::Idle;
        }
      default:
        break;
    }
  }

 private:
  libmcu::States state;
  Application_settings *settings_store, *defaults_store;
  std::span<std::uint8_t> storage_buffer;
  std::uint8_t magic_version;
  std::size_t current_address;
  std::size_t search_address;
  std::uint8_t sequence_number;
  //! @todo Stride for EEPROM?
};

#endif