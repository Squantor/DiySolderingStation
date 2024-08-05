/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC840 series interrupt synchronous UART HAL
 */
#ifndef LPC84X_HAL_UARTSYNC_INT_HPP
#define LPC84X_HAL_UARTSYNC_INT_HPP

#include <LPC84X_hal_uart_common.hpp>

namespace libMcu::hal::usart {
namespace hardware = libMcu::hw::usart;
namespace nvic = libMcu::hw::nvic;

template <libMcu::uartBaseAddress const& uartBaseAddress_, libMcu::nvicBaseAddress const& nvicBaseAddress_, typename transferType>
struct uartSync {
  /**
   * @brief Construct a new asynchronous uart
   */
  uartSync() {}
  /**
   * @brief Initialize
   */
  void initialize() {}
  /**
   * @brief Setup USART to 8n1
   * @param baudRate Baud rate value
   * @return std::uint32_t actual baud rate
   */
  constexpr std::uint32_t init(std::uint32_t baudRate) {
    std::uint32_t baudDivider = CLOCK_MAIN / (baudRate * 16);
    usartPeripheral()->BRG = baudDivider;
    usartPeripheral()->CFG = hardware::CFG::ENABLE | static_cast<std::uint32_t>(uartLength::SIZE_8) |
                             static_cast<std::uint32_t>(uartParity::NONE) | static_cast<std::uint32_t>(uartStop::STOP_1);
    return CLOCK_MAIN / 16 / baudDivider;
  }
  /**
   * @brief Setup USART
   * @param baudRate Baud rate value
   * @param lengthBits bit length of transmissions, see uartLength enum for options
   * @param parity parity type of transmissions, see uartParity enum for options
   * @param stopBits Amount of stop bits, see uartStop enum for options
   * @return std::uint32_t actual baud rate
   */
  constexpr std::uint32_t init(std::uint32_t baudRate, uartLength lengthBits, uartParity parity, uartStop stopBits) {
    std::uint32_t baudDivider = CLOCK_MAIN / (baudRate * 16);
    usartPeripheral()->BRG = baudDivider;
    usartPeripheral()->CFG = hardware::CFG::ENABLE | static_cast<std::uint32_t>(lengthBits) | static_cast<std::uint32_t>(parity) |
                             static_cast<std::uint32_t>(stopBits);
    return CLOCK_MAIN / 16 / baudDivider;
  }
  /**
   * @brief
   * @param buffer data to transmit via uart
   */
  constexpr void transmit(std::span<transferType> buffer) {
    // Copy data
  }
  /**
   * @brief UART interrupt service routine
   */
  constexpr void isr() {}

 private:
  /**
   * @brief access uart registers
   * @return return pointer to peripheral
   */
  static hardware::peripheral* usartPeripheral() {
    return reinterpret_cast<hardware::peripheral*>(uartBaseAddress);
  }
  /**
   * @brief access nvic registers
   * @return return pointer to peripheral
   */
  static nvic::peripheral* nvicPeripheral() {
    return reinterpret_cast<nvic::peripheral*>(nvicBaseAddress);
  }

  static constexpr hwAddressType uartBaseAddress = uartBaseAddress_; /**< UART peripheral address */
  static constexpr hwAddressType nvicBaseAddress = nvicBaseAddress_; /**< NVIC peripheral address */
  // needs a circular buffer datastructure
};  // namespace libMcu::hw::nvic
}  // namespace libMcu::hal::usart

#endif