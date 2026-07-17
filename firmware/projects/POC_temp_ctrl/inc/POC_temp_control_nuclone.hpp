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
#include <drivers/SH1106_i2c.hpp>
#include <drivers/PCF8574.hpp>
#include <drivers/24xxx.hpp>
#include <mid/gfx_display.hpp>
#include <mid/fonts/8x8.hpp>

// constants
constexpr std::uint32_t ticks_per_second = 1000;
constexpr std::size_t max_i2c_transactions = 48;

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
// Power control pins
using PinPowerControl1 = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin06>;
using PinPowerControl2 = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;
// differential amplifier ADC pin
using PinTcAmpType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin07>;
// I2C pins
using PinI2cSclType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin10>;
using PinI2cSdaType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin11>;
// User interface button change interrupt pin with pull up resistor
using Pin_button_expander_type = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin28>;

// function types
using FunctionXtalInType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using FunctionXtalOutType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using FunctionUartDebugTxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0TxOut>;
using FunctionUartDebugRxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0RxIn>;
using FunctionAdcTcAmpType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Adc0In>;
using FunctionI2CSclType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::I2c0SclInOut>;
using FunctionI2CSdaType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::I2c0SdaInOut>;

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
constexpr PinPowerControl1 pin_power_control1;
constexpr PinPowerControl2 pin_power_control2;
constexpr PinTcAmpType pin_tc_amp;
constexpr PinI2cSclType pin_i2c_scl;
constexpr PinI2cSdaType pin_i2c_sda;
constexpr Pin_button_expander_type pin_ui_button_int;
// port instances
constexpr PortMuxType port_mux;
// function instances
constexpr FunctionXtalInType function_xtal_in;
constexpr FunctionXtalOutType function_xtal_out;
constexpr FunctionUartDebugTxType function_debug_uart_tx;
constexpr FunctionUartDebugRxType function_debug_uart_rx;
constexpr FunctionAdcTcAmpType function_adc_tc_amp;
constexpr FunctionI2CSclType function_i2c_scl;
constexpr FunctionI2CSdaType function_i2c_sda;
// interrupt pin channel definitions
constexpr libmcull::syscon::InterruptPins zero_cross_intpin = libmcull::syscon::InterruptPins::PintSel0;
constexpr libmcull::pin_int::InterruptPins zero_cross_intchan = libmcull::pin_int::InterruptPins::PintSel0;
constexpr libmcull::syscon::InterruptPins ui_button_intpin = libmcull::syscon::InterruptPins::PintSel1;
constexpr libmcull::pin_int::InterruptPins ui_button_intchan = libmcull::pin_int::InterruptPins::PintSel1;

// variable externs
extern volatile std::uint32_t ticks;             // amount of ticks passed sinds startup
extern volatile std::uint32_t zerocross_counts;  // amount of zerocrosses passed sinds startup
extern libmcu::I2cDeviceAddress SH1106_i2c_address;
extern libmcu::I2cDeviceAddress PCF8574_i2c_address;
extern libmcu::I2cDeviceAddress eeprom_24xxx_i2c_address;

// Clock configurations
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nuclone_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart_0_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::I2C0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  i2c_0_clock_config;
// Low level peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systick_peripheral;
extern libmcull::adc::Adc<libmcuhw::Adc0Address> adc_peripheral;
extern libmcull::pin_int::Pinint<libmcuhw::PinintAddress> pinint_peripheral;
extern libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 1024> ll_usart_peripheral;
extern libmcull::i2c::I2cInterrupt<libmcuhw::I2c0Address> ll_i2c_peripheral;
// Hal peripheral externs
extern libmcuhal::usart::Uart<ll_usart_peripheral, char> usart_peripheral;
extern libmcuhal::i2c::I2c<ll_i2c_peripheral, max_i2c_transactions> i2c_peripheral;
// driver externs
extern libmcudrv::SH1106::Generic128x64 display_config;
extern libmcudrv::SH1106::SH1106<i2c_peripheral, SH1106_i2c_address, display_config, libmcull::Assert_bkpt> ui_display;
extern libmcudrv::PCF8574::PCF8574<i2c_peripheral, PCF8574_i2c_address> ui_port_expander;
extern libmcudrv::eeprom_24xxx::Generic_24xxx02 eeprom_24xxx_config;
extern libmcudrv::eeprom_24xxx::Eeprom_24xxx<i2c_peripheral, eeprom_24xxx_i2c_address, eeprom_24xxx_config> eeprom_24xxx;
// middleware externs
extern libmcumid::Gfx_display<ui_display> application_display;

/**
 * @brief initialize the board
 */
void board_init(void);
/**
 * @brief Progress all hardware peripherals
 */
void board_progress(void);
/**
 * @brief checks if mains power is present
 * @return true mains power present
 * @return false mains power not present
 */
bool is_mains_present(void);

/**
 * @brief Set the iron pin multiplexers
 * @param mux1 mux value, see HSI for what pins these are
 * @param mux2 mux value, see HSI for what pins these are
 */
void set_multiplexers(std::uint32_t mux1, std::uint32_t mux2);

/**
 * @brief Setup hardware to be safe when USB powered
 * This entails setting muxes to 0, power stage to 0 and resetting power control states
 */
void set_safe_usb_powered(void);

/**
 * @brief Set Power control 1 pin
 * @param on true for high, false for low
 */
void set_power_control_1(bool on);

/**
 * @brief Set Power control 2 pin
 * @param on true for high, false for low
 */
void set_power_control_2(bool on);

#endif