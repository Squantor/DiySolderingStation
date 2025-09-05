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
using pinXtalInType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using pinXtalOutType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// bootloader and uart pins
using pinBootloaderType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;
using pinDebugUartTxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using pinDebugUartRxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;
// 5V presence detection via 5.6K 10K ohm resistive divider
using pinPowerDetectType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin04>;
// multiplexer port
using portMuxType = libmcuhw::Port<libmcuhw::IoPorts::Port1>;
// multiplexer 1
using pinMux1s0Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin00>;
using pinMux1s1Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin01>;
using pinMux1s2Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin02>;
// multiplexer 2
using pinMux2s0Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;
using pinMux2s1Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin06>;
using pinMux2s2Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin07>;

// differential amplifier ADC pin
using pinTcAmpType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin07>;

// function types
using functionXtalInType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using functionXtalOutType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using functionUartDebugTxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0TxOut>;
using functionUartDebugRxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0RxIn>;
using functionAdcTcAmpType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Adc0In>;

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
// Clock configurations
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nuclone_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart_0_clock_config;
// Low level peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
extern libmcull::adc::Adc<libmcuhw::Adc0Address> adcPeripheral;
extern libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 128> ll_usart_peripheral;
// Hal peripheral externs
extern libmcuhal::usart::UartInterrupt<ll_usart_peripheral, char> usart_peripheral;

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