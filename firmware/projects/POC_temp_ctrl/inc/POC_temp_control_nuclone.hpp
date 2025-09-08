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

#define TICKS_PER_S 1000

// pin types
// Crystal osillator pins
using PinXtalInType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using PinXtalOutType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// bootloader and uart pins
using PinBootloaderType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;
using PinDebugUartTxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using PinDebugUartRxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;
// 5V presence detection via 5.6K 10K ohm resistive divider
using PinPowerDetectType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin04>;
// multiplexer port
using PortMuxType = libmcuhw::Port<libmcuhw::IoPorts::Port1>;
// multiplexer 1
using PinMux1s0Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin00>;
using PinMux1s1Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin01>;
using PinMux1s2Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin02>;
// multiplexer 2
using PinMux2s0Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;
using PinMux2s1Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin06>;
using PinMux2s2Type = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin07>;
// Zerocross detection pin, 10K pulldown, open PNP emitter to 3.3V
using PinZeroCross = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin17>;
// differential amplifier ADC pin
using PinTcAmpType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin07>;

// function types
using FunctionXtalInType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using FunctionXtalOutType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using FunctionUartDebugTxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0TxOut>;
using FunctionUartDebugRxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0RxIn>;
using FunctionAdcTcAmpType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Adc0In>;

// pin instances
constexpr PinXtalInType pin_xtal_in;
constexpr PinXtalOutType pin_xtal_out;
constexpr PinBootloaderType pin_bootload;
constexpr PinDebugUartTxType pin_debug_uart_tx;
constexpr PinDebugUartRxType pin_debug_uart_rx;
constexpr PinPowerDetectType pin_power_detect;
constexpr PinMux1s0Type pin_mux1s0;
constexpr PinMux1s1Type pin_mux1s1;
constexpr PinMux1s2Type pin_mux1s2;
constexpr PinMux2s0Type pin_mux2s0;
constexpr PinMux2s1Type pin_mux2s1;
constexpr PinMux2s2Type pin_mux2s2;
constexpr PinZeroCross pin_zero_cross;
constexpr PinTcAmpType pin_tc_amp;
// port instances
constexpr PortMuxType port_mux;
// function instances
constexpr FunctionXtalInType function_xtal_in;
constexpr FunctionXtalOutType function_xtal_out;
constexpr FunctionUartDebugTxType function_debug_uart_tx;
constexpr FunctionUartDebugRxType function_debug_uart_rx;
constexpr FunctionAdcTcAmpType function_adc_tc_amp;

// Clock configurations
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nuclone_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart_0_clock_config;
// Low level peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systick_peripheral;
extern libmcull::adc::Adc<libmcuhw::Adc0Address> adc_peripheral;
extern libmcull::pin_int::Pinint<libmcuhw::PinintAddress> pinint_peripheral;
extern libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 128> ll_usart_peripheral;
// Hal peripheral externs
extern libmcuhal::usart::UartInterrupt<ll_usart_peripheral, char> usart_peripheral;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void BoardInit(void);
/**
 * @brief checks if mains power is present
 * @return true mains power present
 * @return false mains power not present
 */
bool IsMainsPresent(void);

/**
 * @brief Set the iron pin multiplexers
 * @param mux1 mux value, see HSI for what pins these are
 * @param mux2 mux value, see HSI for what pins these are
 */
void SetMultiplexers(std::uint32_t mux1, std::uint32_t mux2);

/**
 * @brief Setup hardware to be safe when USB powered
 * This entails setting muxes to 0, power stage to 0 and resetting power control states
 */
void SetSafeUsbPowered(void);

#endif