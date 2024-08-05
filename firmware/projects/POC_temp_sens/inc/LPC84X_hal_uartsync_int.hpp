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

template <libMcu::uartBaseAddress const& uartBaseAddress_, typename transferType>
struct uartSync {
  /**
   * @brief Construct a new asynchronous uart
   */
  uartSync() : transactionWriteState{detail::synchonousStates::IDLE}, transactionReadState{detail::synchonousStates::IDLE} {}
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
   * @brief Claim the Usart interface
   * @return IN_USE when already in use
   * @return CLAIMED when the claim has been successful
   */
  constexpr libMcu::results claim(void) {
    if ((transactionWriteState != detail::synchonousStates::IDLE) && (transactionReadState != detail::synchonousStates::IDLE)) {
      return libMcu::results::IN_USE;
    }
    transactionWriteState = detail::synchonousStates::CLAIMED;
    transactionReadState = detail::synchonousStates::CLAIMED;
    return libMcu::results::CLAIMED;
  }
  /**
   * @brief Unclaim the Usart interface
   * @return ERROR when already idle or inconsistent, possible programming error!
   * @return BUSY when still executing a transaction
   * @return UNCLAIMED when unclaim sucessful
   */
  constexpr libMcu::results unclaim(void) {
    if ((transactionWriteState == detail::synchonousStates::TRANSACTING) ||
        (transactionReadState == detail::synchonousStates::TRANSACTING)) {
      return libMcu::results::BUSY;
    } else if ((transactionWriteState == detail::synchonousStates::CLAIMED) &&
               (transactionReadState == detail::synchonousStates::CLAIMED)) {
      transactionWriteState = detail::synchonousStates::IDLE;
      transactionReadState = detail::synchonousStates::IDLE;
      return libMcu::results::UNCLAIMED;
    } else {
      return libMcu::results::ERROR;
    }
  }
  /**
   * @brief Start a read transaction
   * @param buffer buffer of data to read
   * @return ERROR if not claimed interface or busy
   * @return STARTED when transaction started
   */
  constexpr libMcu::results startRead(std::span<transferType> buffer) {
    if (transactionReadState != detail::synchonousStates::CLAIMED) {
      return libMcu::results::ERROR;
    }
    // store transaction information
    transactionReadIndex = 0u;
    transactionReadData = buffer;
    transactionReadState = detail::synchonousStates::TRANSACTING;
    return libMcu::results::STARTED;
  }
  /**
   * @brief Start a write transaction
   * @param buffer buffer of data to read
   * @return ERROR if not claimed interface or busy
   * @return STARTED when transaction started
   */
  constexpr libMcu::results startWrite(std::span<transferType> buffer) {
    if (transactionWriteState != detail::synchonousStates::CLAIMED) {
      return libMcu::results::ERROR;
    }
    // store transaction information
    transactionWriteIndex = 0u;
    transactionWriteData = buffer;
    transactionWriteState = detail::synchonousStates::TRANSACTING;
    // TODO write first data in UART register
    return libMcu::results::STARTED;
  }
  /**
   * @brief continue started read transaction
   * @return ERROR if transaction has not started
   * @return BUSY if transaction is still in progress
   * @return DONE if transaction is done and buffer filled with data
   */
  constexpr libMcu::results progressRead(void) {
    if (transactionReadState != detail::synchonousStates::TRANSACTING) {
      return libMcu::results::ERROR;
    }
    if (usartPeripheral()->STAT & hardware::STAT::RXRDY) {
      transactionReadData[transactionReadIndex] = static_cast<transferType>(usartPeripheral()->RXDAT);
      transactionReadIndex++;
      if (transactionReadData.size() == transactionReadIndex) {
        transactionReadState = detail::synchonousStates::CLAIMED;
        return libMcu::results::DONE;
      }
    }
    return libMcu::results::BUSY;
  }
  /**
   * @brief continue started write transaction
   * @return ERROR if transaction has not started
   * @return BUSY if transaction is still in progress
   * @return DONE if transaction is done and buffer of data has been written
   */
  constexpr libMcu::results progressWrite(void) {
    if (transactionWriteState != detail::synchonousStates::TRANSACTING) {
      return libMcu::results::ERROR;
    }
    std::uint32_t status = usartPeripheral()->STAT;
    if (status & hardware::STAT::TXRDY) {
      if (transactionWriteData.size() > transactionWriteIndex) {
        usartPeripheral()->TXDAT = static_cast<std::uint32_t>(transactionWriteData[transactionWriteIndex]);
        transactionWriteIndex++;
      } else {
        if (status & hardware::STAT::TXIDLE) {
          transactionWriteState = detail::synchonousStates::CLAIMED;
          return libMcu::results::DONE;
        }
      }
    }
    return libMcu::results::BUSY;
  }

 private:
  /**
   * @brief get registers from peripheral
   * @return return pointer to peripheral
   */
  static hardware::peripheral* usartPeripheral() {
    return reinterpret_cast<hardware::peripheral*>(uartBaseAddress);
  }

  static constexpr hwAddressType uartBaseAddress = uartBaseAddress_; /**< uart peripheral address */
  detail::synchonousStates transactionWriteState;                    /**< usart write transaction state */
  detail::synchonousStates transactionReadState;                     /**< usart read transaction state */
  std::size_t transactionWriteIndex;                                 /**< transaction write buffer index */
  std::size_t transactionReadIndex;                                  /**< transaction read buffer index */
  std::span<transferType> transactionWriteData;                      /**< data to write */
  std::span<transferType> transactionReadData;                       /**< where to put read data in */
};
}  // namespace libMcu::hal::usart

#endif