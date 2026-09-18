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
      sequence_number{0} {
    std::size_t settings_record_size = sizeof(detail::Settings_storage_record<Application_settings>);
    storage_stride = (storage_driver.page_size() * (settings_record_size / storage_driver.page_size()));
    if (settings_record_size % storage_driver.page_size() != 0) {
      storage_stride += storage_driver.page_size();
    }
  }
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
   * @return Result
   */
  libmcu::Results save(Application_settings &settings) {
    if (state != libmcu::States::Idle) {
      return libmcu::Results::Busy;
    }
    current_address += storage_stride;
    if (search_address >= storage_driver.size())
      search_address = 0;
    sequence_number++;
    detail::Settings_storage_record<Application_settings> *record =
      reinterpret_cast<detail::Settings_storage_record<Application_settings> *>(storage_buffer.data());
    record->magic_version = magic_version;
    record->sequence_number = sequence_number;
    record->checksum = 0;
    record->settings = settings;
    storage_driver.write(current_address, storage_buffer, this);
    state = libmcu::States::busy_writing;
    return libmcu::Results::busy_writing;
  }
  /**
   * @brief Load settings from storage
   * @param settings Reference to settings
   * @return Result
   */
  libmcu::Results load(Application_settings &settings) {
    if (state != libmcu::States::Idle) {
      return libmcu::Results::Busy;
    }
    settings_store = &settings;
    storage_driver.read(current_address, storage_buffer, this);
    state = libmcu::States::busy_reading;
    return libmcu::Results::busy_reading;
  }
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
      // looking through EEPROM for the newest settings
      case libmcu::States::Initializing:
        if (result == libmcu::Results::NoError) {
          detail::Settings_storage_record<Application_settings> *record =
            reinterpret_cast<detail::Settings_storage_record<Application_settings> *>(storage_buffer.data());

          // analyze record
          if ((record->magic_version == magic_version) && (record->checksum == storage_buf_checksum())) {
            if (sequence_number < record->sequence_number) {
              sequence_number = record->sequence_number;
              current_address = search_address;
              *settings_store = record->settings;
            } else if (sequence_number == 0xFF) {
              // we where at the end of the sequence number, record lower one
              sequence_number = record->sequence_number;
              current_address = search_address;
              *settings_store = record->settings;
            }
          }

          // go to next page
          search_address += storage_stride;
          // did we go to the end?
          if (search_address >= storage_driver.size()) {
            // did we find something?
            if (current_address != storage_driver.size()) {
              // We did, read from recorded address
              storage_driver.read(current_address, storage_buffer, this);
              state = libmcu::States::busy_reading;
            } else {
              // We did not, write default settings at address 0
              //! @todo what if there is something already there?
              current_address = 0;
              for (auto &element : storage_buffer) {
                element = 0;
              }
              record->magic_version = magic_version;
              record->sequence_number = 1;
              record->settings = *defaults_store;
              record->checksum = storage_buf_checksum();
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
  std::size_t storage_stride;
  std::uint8_t sequence_number;

  std::uint16_t storage_buf_checksum() {
    uint16_t sum = storage_buffer[0] + storage_buffer[1];
    for (std::size_t i = 4; i < storage_buffer.size(); i++) {
      sum += storage_buffer[i];
    }
    return sum;
  }
};

#endif