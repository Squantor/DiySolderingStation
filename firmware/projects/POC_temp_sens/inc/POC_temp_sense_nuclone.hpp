/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#ifndef POC_TEMP_SENSE_NUCLONE_HPP
#define POC_TEMP_SENSE_NUCLONE_HPP

#define CLOCK_XTAL (12'000'000u)
#define CLOCK_EXT_IN (0u)
#define CLOCK_CPU (30'000'000u)
#define CLOCK_AHB (30'000'000u)
#define CLOCK_MAIN (60'000'000u)

#include <ringbuffer.hpp>
#include <nxp/libmcu_LPC845M301BD48.hpp>
#include <LPC84X_hal_uartasync_pol.hpp>
#include <LPC84X_hal_uartsync_int.hpp>

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libMcu::hw::pin<libMcu::hw::IOports::PORT0, libMcu::hw::IOpins::PIN08>;
using pinXtalOutType = libMcu::hw::pin<libMcu::hw::IOports::PORT0, libMcu::hw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libMcu::hw::pin<libMcu::hw::IOports::PORT0, libMcu::hw::IOpins::PIN12>;
using pinDebugUartTxType = libMcu::hw::pin<libMcu::hw::IOports::PORT0, libMcu::hw::IOpins::PIN25>;
using pinDebugUartRxType = libMcu::hw::pin<libMcu::hw::IOports::PORT0, libMcu::hw::IOpins::PIN24>;
// 5V presence detection via 5.6K 10K ohm resistive divider
// multiplexer 1
// multiplexer 2
// differential amplifier ADC pin

// function types
using functionXtalInType = libMcu::hw::swm::pinFunction<libMcu::hw::swm::pinFunctions::XTALIN>;
using functionXtalOutType = libMcu::hw::swm::pinFunction<libMcu::hw::swm::pinFunctions::XTALOUT>;
using functionUartDebugTxType = libMcu::hw::swm::pinFunction<libMcu::hw::swm::pinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libMcu::hw::swm::pinFunction<libMcu::hw::swm::pinFunctions::U0_RXD_I>;

// pin instances
constexpr pinXtalInType xtalInPin;
constexpr pinXtalOutType xtalOutPin;
constexpr pinBootloaderType bootloadPin;
constexpr pinDebugUartTxType debugUartTxPin;
constexpr pinDebugUartRxType debugUartRxPin;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;

// peripheral externs
extern libMcu::ll::iocon::iocon<libMcu::hw::ioconAddress> ioconPeripheral;
extern libMcu::ll::swm::swm<libMcu::hw::swmAddress> swmPeriperhal;
extern libMcu::ll::gpio::gpio<libMcu::hw::gpioAddress> gpioPeripheral;
extern libMcu::ll::syscon::syscon<libMcu::hw::sysconAddress> sysconPeripheral;
extern libMcu::ll::systick::systick<libMcu::hw::systickAddress> systickPeripheral;
extern libMcu::hal::usart::uartSync<libMcu::hw::usart0Address, libMcu::hw::nvicAddress, std::uint8_t, 128> usartPeripheral;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);

#endif