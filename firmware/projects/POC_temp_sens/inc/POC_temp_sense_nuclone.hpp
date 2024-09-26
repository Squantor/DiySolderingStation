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

#include <nxp/libmcu_LPC845M301BD48_hal.hpp>

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN08>;
using pinXtalOutType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN12>;
using pinDebugUartTxType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN25>;
using pinDebugUartRxType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN24>;
// 5V presence detection via 5.6K 10K ohm resistive divider
using pinPowerDetectType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN04>;
// multiplexer port
using portMuxType = libMcuLL::hw::port<libMcuLL::hw::IOports::PORT1>;
// multiplexer 1
using pinMux1s0Type = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT1, libMcuLL::hw::IOpins::PIN00>;
using pinMux1s1Type = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT1, libMcuLL::hw::IOpins::PIN01>;
using pinMux1s2Type = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT1, libMcuLL::hw::IOpins::PIN02>;
// multiplexer 2
using pinMux2s0Type = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT1, libMcuLL::hw::IOpins::PIN05>;
using pinMux2s1Type = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT1, libMcuLL::hw::IOpins::PIN06>;
using pinMux2s2Type = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT1, libMcuLL::hw::IOpins::PIN07>;

// differential amplifier ADC pin
using pinDiffAmpInputType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN07>;

// function types
using functionXtalInType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALIN>;
using functionXtalOutType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALOUT>;
using functionUartDebugTxType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::U0_RXD_I>;

// pin instances
constexpr pinXtalInType xtalInPin;
constexpr pinXtalOutType xtalOutPin;
constexpr pinBootloaderType bootloadPin;
constexpr pinDebugUartTxType debugUartTxPin;
constexpr pinDebugUartRxType debugUartRxPin;
constexpr pinPowerDetectType PowerDetectPin;
constexpr pinMux1s0Type mux1s0Pin;
constexpr pinMux1s1Type mux1s1Pin;
constexpr pinMux1s2Type mux1s2Pin;
constexpr pinMux2s0Type mux2s0Pin;
constexpr pinMux2s1Type mux2s1Pin;
constexpr pinMux2s2Type mux2s2Pin;
constexpr pinDiffAmpInputType diffAmpInputPin;
// port instances
constexpr portMuxType muxPort;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;

// peripheral externs
extern libMcuLL::iocon::iocon<libMcuLL::hw::ioconAddress> ioconPeripheral;
extern libMcuLL::swm::swm<libMcuLL::hw::swmAddress> swmPeriperhal;
extern libMcuLL::gpio::gpio<libMcuLL::hw::gpioAddress> gpioPeripheral;
extern libMcuLL::syscon::syscon<libMcuLL::hw::sysconAddress> sysconPeripheral;
extern libMcuLL::systick::systick<libMcuLL::hw::systickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libMcuLL::hw::usart0Address, libMcuLL::hw::nvicAddress, char, 128> usartPeripheral;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);
/**
 * @brief checks if mains power is present
 * @return true mains power present
 * @return false mains power not present
 */
bool isMainsPresent(void);

/**
 * @brief Set the iron pin multiplexers
 * @param mux1 mux value, see HSI for what pins these are
 * @param mux2 mux value, see HSI for what pins these are
 */
void setMultiplexers(std::uint32_t mux1, std::uint32_t mux2);

/**
 * @brief Setup hardware to be safe when USB powered
 * This entails setting muxes to 0, power stage to 0 and resetting power control states
 */
void setSafeUsbPowered(void);

#endif