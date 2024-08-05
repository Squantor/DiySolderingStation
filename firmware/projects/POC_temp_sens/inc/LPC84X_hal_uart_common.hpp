/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC840 series polling asynchronous UART HAL
 */
#ifndef LPC84X_HAL_UART_COMMON_HPP
#define LPC84X_HAL_UART_COMMON_HPP

namespace libMcu::hal::usart {
namespace hardware = libMcu::hw::usart;

/**
 * @brief amount of bits to transmit
 */
enum class uartLength : std::uint32_t {
  SIZE_7 = hardware::CFG::DATALEN7BIT, /**< USART transmit length of 7 bits */
  SIZE_8 = hardware::CFG::DATALEN8BIT, /**< USART transmit length of 8 bits */
  SIZE_9 = hardware::CFG::DATALEN9BIT, /**< USART transmit length of 9 bits */
};

/**
 * @brief Parity bit options
 */
enum class uartParity : std::uint32_t {
  NONE = hardware::CFG::PARITY_NONE, /**< No parity */
  EVEN = hardware::CFG::PARITY_EVEN, /**< Even parity */
  ODD = hardware::CFG::PARITY_ODD,   /**< Odd parity */
};

/**
 * @brief stop bit options
 */
enum class uartStop : std::uint32_t {
  STOP_1 = hardware::CFG::STOPBIT1, /**< 1 stop bit */
  STOP_2 = hardware::CFG::STOPBIT2, /**< 2 stop bits */
};

/**
 * @brief Uart status bits
 *
 * These bit patterns match the USART STAT register settings
 */
enum uartStatus : std::uint32_t {
  RXRDY = hardware::STAT::RXRDY,               /**< Receiver ready flag, Read only */
  RXIDLE = hardware::STAT::RXIDLE,             /**< Receiver idle, Read only */
  TXRDY = hardware::STAT::TXRDY,               /**< Transmitter ready, Read only  */
  TXIDLE = hardware::STAT::TXIDLE,             /**< Transmitter idle, Read only */
  CTS = hardware::STAT::CTS,                   /**< CTS signal state, Read only */
  DELTACTS = hardware::STAT::DELTACTS,         /**< Change detected in CTS signal, write 1 clear */
  TXDISINT = hardware::STAT::TXDISINT,         /**< Transmitter disabled confirmation, read only  */
  OVERRUNINT = hardware::STAT::OVERRUNINT,     /**< Overrun error interrupt flag, write 1 clear */
  RXBRK = hardware::STAT::RXBRK,               /**< Received break, read only */
  DELTARXBRK = hardware::STAT::DELTARXBRK,     /**< Change detected in receiver break, write 1 clear */
  START = hardware::STAT::START,               /**< Start condition detected, write 1 clear */
  FRAMERRINT = hardware::STAT::FRAMERRINT,     /**< Frame error interrupt flag, write 1 clear */
  PARITYERRINT = hardware::STAT::PARITYERRINT, /**< Parity error interrupt flag, write 1 clear */
  RXNOISEINT = hardware::STAT::RXNOISEINT,     /**< Recieved noise interrupt flag, write 1 clear*/
  ABERR = hardware::STAT::ABERR,               /**< Autobaud error flag, write 1 clears */
};

namespace detail {

enum class synchonousStates : std::uint8_t {
  IDLE,        /**< Interface is idle, ready to be claimed */
  CLAIMED,     /**< Interface is claimed, ready to transact */
  TRANSACTING, /**< Interface is busy with a transaction */
};
}  // namespace detail

}  // namespace libMcu::hal::usart

#endif