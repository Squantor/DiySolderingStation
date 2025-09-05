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

#include <nxp/libmcu_LPC845M301BD48_hal.hpp>

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN08>;
using pinXtalOutType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN12>;
using pinDebugUartTxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN25>;
using pinDebugUartRxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN24>;
// 5V presence detection via 5.6K 10K ohm resistive divider
using pinPowerDetectType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN04>;
// multiplexer port
using portMuxType = libMcuHw::port<libMcuHw::IOports::PORT1>;
// multiplexer 1
using pinMux1s0Type = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN00>;
using pinMux1s1Type = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN01>;
using pinMux1s2Type = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN02>;
// multiplexer 2
using pinMux2s0Type = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN05>;
using pinMux2s1Type = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN06>;
using pinMux2s2Type = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN07>;

// differential amplifier ADC pin
using pinTcAmpType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN07>;

// function types
using functionXtalInType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALIN>;
using functionXtalOutType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALOUT>;
using functionUartDebugTxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_RXD_I>;
using functionAdcTcAmpType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::ADC_0_I>;

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
constexpr pinTcAmpType TcAmpPin;
// port instances
constexpr portMuxType muxPort;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;
constexpr functionAdcTcAmpType adcTcAmpFunction;

// peripheral externs
extern libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
extern libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
extern libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
extern libMcuLL::syscon::syscon<libMcuHw::sysconAddress> syscon_peripheral;
extern libMcuLL::systick::systick<libMcuHw::systickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libMcuHw::usart0Address, libMcuHw::nvicAddress, char, 128> usart_peripheral;
extern libMcuLL::adc::adc<libMcuHw::adc0Address> adcPeripheral;
inline constexpr libMcuHw::clock::clockConfig<
  libMcuHw::clock::clockInputSources::XTAL, 12'000'000u, 30'000'000u, libMcuHw::clock::periSource::MAIN,
  libMcuHw::clock::periSource::MAIN, libMcuHw::clock::periSource::MAIN, libMcuHw::clock::periSource::MAIN,
  libMcuHw::clock::periSource::MAIN, libMcuHw::clock::periSource::MAIN, libMcuHw::clock::periSource::MAIN,
  libMcuHw::clock::periSource::MAIN, libMcuHw::clock::periSource::MAIN, libMcuHw::clock::periSource::MAIN,
  libMcuHw::clock::periSource::SYS_PLL>
  diySolderClockConfig;

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