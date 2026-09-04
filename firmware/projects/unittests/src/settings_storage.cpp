/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file settings_storage.cpp
 * @brief Unitttests for settings storage class
 */
#include <cstdint>
#include <array>
#include <span>
#include <algorithm>
#include <minunit.h>
#include <pc/libmcu_PC_hal.hpp>
#include "settings_storage.hpp"

/**
 * @brief Settings storage test structure
 */
struct Test_storage {
  std::uint8_t value_one;
  std::uint16_t value_two;
  std::uint32_t value_three;
};
/**
 * @brief Storage driver mock
 */
struct Storage_driver_mock {
  Storage_driver_mock(std::span<std::uint8_t> storage, std::size_t page_size)
    : storage{storage}, storage_page_size{page_size}, storage_size{storage.size()}, last_call_callback{nullptr} {}
  void read(std::size_t address, std::span<std::uint8_t> buffer, libmcu::NonBlocking* callback = nullptr) {
    if (address > storage.size()) {
      minunit_report("Storage_driver_mock: Read out of bounds\n");
      return;
    }
    for (std::size_t index = 0; index < buffer.size(); index++) {
      buffer[index] = storage[address + index];
    }
    last_call_callback = callback;
  }
  void write(std::size_t address, std::span<const std::uint8_t> buffer, libmcu::NonBlocking* callback = nullptr) {
    if (address > storage.size()) {
      minunit_report("Storage_driver_mock: Write out of bounds\n");
      return;
    }
    for (std::size_t index = 0; index < buffer.size(); index++) {
      storage[address + index] = buffer[index];
    }
    last_call_callback = callback;
  }
  void call_callback(libmcu::Results result) {
    if (last_call_callback != nullptr) {
      last_call_callback->callback(result);
    } else {
      minunit_report("Storage_driver_mock: No callback stored\n");
    }
  }
  constexpr std::size_t size() const noexcept {
    return storage_size;
  }

  constexpr std::size_t page_size() const noexcept {
    return storage_page_size;
  }

 private:
  std::span<std::uint8_t> storage;
  std::size_t storage_page_size;
  std::size_t storage_size;
  libmcu::NonBlocking* last_call_callback;
};

std::array<std::uint8_t, 128> storage_buffer;
std::array<std::uint8_t, 16> settings_buffer;
Storage_driver_mock storage_driver_dut(storage_buffer, 16);
Settings_storage<Test_storage, storage_driver_dut> settings_storage_dut(settings_buffer, 0x32);

MINUNIT_SETUP(settings_storage_setup) {
  storage_buffer.fill(0xFF);
  MINUNIT_PASS();
}

MINUNIT_TEARDOWN(settings_storage_teardown) {
  settings_storage_dut.deinit();
  MINUNIT_PASS();
}

// Test initialization
MINUNIT_ADD(settings_storage_init_empty, settings_storage_setup, settings_storage_teardown) {
  std::size_t timeout_count = 1000;
  Test_storage test_storage{1, 2, 3};
  Test_storage test_storage_defaults{4, 5, 6};
  MINUNIT_CHECK(settings_storage_dut.get_state() == libmcu::States::Uninitialized);
  settings_storage_dut.init(test_storage, test_storage_defaults);
  MINUNIT_CHECK(settings_storage_dut.get_state() == libmcu::States::Initializing);
  while (timeout_count > 0 && settings_storage_dut.get_state() != libmcu::States::Idle) {
    settings_storage_dut.progress();
    timeout_count--;
    storage_driver_dut.call_callback(libmcu::Results::NoError);
  }
  // check if defaults settings are written to storage
  MINUNIT_CHECK(test_storage.value_one == 4);
  MINUNIT_CHECK(test_storage.value_two == 5);
  MINUNIT_CHECK(test_storage.value_three == 6);
  // check if default settings are written to address 0
  MINUNIT_CHECK(storage_buffer[0] == 0x32);
  MINUNIT_CHECK(storage_buffer[1] == 0x00);
  MINUNIT_CHECK(storage_buffer[2] == 0x00);
  MINUNIT_CHECK(storage_buffer[3] == 0x00);
  MINUNIT_CHECK(storage_buffer[4] == 0x04);
  MINUNIT_CHECK(storage_buffer[6] == 0x05);
  MINUNIT_CHECK(storage_buffer[7] == 0x00);
  MINUNIT_CHECK(storage_buffer[8] == 0x06);
  MINUNIT_CHECK(storage_buffer[9] == 0x00);
  MINUNIT_CHECK(storage_buffer[10] == 0x00);
  MINUNIT_CHECK(storage_buffer[11] == 0x00);
  MINUNIT_CHECK(storage_buffer[12] == 0x00);
  MINUNIT_CHECK(storage_buffer[13] == 0x00);
  MINUNIT_CHECK(storage_buffer[14] == 0x00);
  MINUNIT_CHECK(storage_buffer[15] == 0x00);
  MINUNIT_CHECK(settings_storage_dut.get_state() == libmcu::States::Idle);
  MINUNIT_CHECK(timeout_count > 0);
}

// test init with already present settings
MINUNIT_ADD(settings_storage_init_not_empty, settings_storage_setup, settings_storage_teardown) {
  std::size_t timeout_count = 1000;
  Test_storage test_storage{1, 2, 3};
  Test_storage test_storage_defaults{4, 5, 6};
  detail::Settings_storage_record<Test_storage>* record =
    reinterpret_cast<detail::Settings_storage_record<Test_storage>*>(settings_buffer.data());
  record->magic_version = 0x32;
  record->sequence_number = 0;
  record->checksum = 0;
  record->settings.value_one = 7;
  record->settings.value_two = 8;
  record->settings.value_three = 9;
  storage_driver_dut.write(0, settings_buffer);
  MINUNIT_CHECK(settings_storage_dut.get_state() == libmcu::States::Uninitialized);
  settings_storage_dut.init(test_storage, test_storage_defaults);
  while (timeout_count > 0 && settings_storage_dut.get_state() != libmcu::States::Idle) {
    settings_storage_dut.progress();
    timeout_count--;
    storage_driver_dut.call_callback(libmcu::Results::NoError);
  }
  // check if present settings are written to storage
  MINUNIT_CHECK(test_storage.value_one == 7);
  MINUNIT_CHECK(test_storage.value_two == 8);
  MINUNIT_CHECK(test_storage.value_three == 9);
}

// test init with already present settings and wrapping sequence numbers
// test init with some pages filled with different data
// test init with some pages filled with different data and wrapping sequence numbers
// test settings write
// test settings write with wrapping sequence numbers
// test settings read