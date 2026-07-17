/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file POC_temp_control_nuclone.cpp
 * @brief board support code for power control proof of concept board
 */
#include <POC_temp_control_nuclone.hpp>
#include <nxp/libmcu_LPC845M301BD48_hal.hpp>
#include <drivers/SH1106_i2c.hpp>
#include <drivers/PCF8574.hpp>
#include <drivers/24xxx.hpp>
#include <mid/gfx_display.hpp>
#include <mid/fonts/8x8.hpp>
#include <application.hpp>

libmcu::I2cDeviceAddress SH1106_i2c_address{0x3C};
libmcu::I2cDeviceAddress PCF8574_i2c_address{0x27};
libmcu::I2cDeviceAddress eeprom_24xxx_i2c_address{0x50};

libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
libmcull::systick::Systick<libmcuhw::SystickAddress> systick_peripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvicPeripheral;
libmcull::adc::Adc<libmcuhw::Adc0Address> adc_peripheral;
libmcull::pin_int::Pinint<libmcuhw::PinintAddress> pinint_peripheral;
libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 1024> ll_usart_peripheral;
libmcull::i2c::I2cInterrupt<libmcuhw::I2c0Address> ll_i2c_peripheral;

libmcuhal::usart::Uart<ll_usart_peripheral, char> usart_peripheral;
libmcuhal::i2c::I2c<ll_i2c_peripheral, max_i2c_transactions> i2c_peripheral;

libmcudrv::SH1106::Generic128x64 display_config;
libmcudrv::SH1106::SH1106<i2c_peripheral, SH1106_i2c_address, display_config, libmcull::Assert_bkpt> ui_display;
libmcudrv::PCF8574::PCF8574<i2c_peripheral, PCF8574_i2c_address> ui_port_expander;
libmcudrv::eeprom_24xxx::Generic_24xxx02 eeprom_24xxx_config;
libmcudrv::eeprom_24xxx::Eeprom_24xxx<i2c_peripheral, eeprom_24xxx_i2c_address, eeprom_24xxx_config> eeprom_24xxx;

libmcumid::Gfx_display<ui_display> application_display;

volatile std::uint32_t ticks;

extern "C" {
/**
 * @brief systick interrupt handler
 */
void SysTick_Handler(void) {
  systick_peripheral.Isr();
}
/**
 * @brief usart interrupt handler
 */
void USART0_IRQHandler(void) {
  ll_usart_peripheral.InterruptHandler();
}
/**
 * @brief i2c interrupt handler
 */
void I2C0_IRQHandler(void) {
  ll_i2c_peripheral.InterruptHandler();
}
/**
 * @brief zerocross interrupt handler
 */
void PIN_INT0_IRQHandler(void) {
  application::solder_iron_controller.zero_cross_isr();
  pinint_peripheral.ClearChannel(libmcull::pin_int::InterruptPins::PintSel0);
}
/**
 * @brief I2C port expander interrupt handler
 */
void PIN_INT1_IRQHandler(void) {
  ui_port_expander.Isr();
  pinint_peripheral.ClearChannel(ui_button_intchan);
}
}

auto systick_isr_lambda = []() {
  ticks = ticks + 1;
  application::solder_iron_controller.systick_isr(ticks);
};

void board_init(void) {
  ticks = 0;
  // clock, power and reset enables/clears
  syscon_peripheral.PowerPeripherals(libmcull::syscon::power_options::SysOsc | libmcull::syscon::power_options::Adc);
  syscon_peripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::Uart0 | libmcull::syscon::peripheral_clocks_0::Adc |
      libmcull::syscon::peripheral_clocks_0::GpioInt | libmcull::syscon::peripheral_clocks_0::I2c0,
    0);
  syscon_peripheral.SetIoconGlitchFiltDivider(libmcull::syscon::IoconGlitchFilters::Filter6, 255);
  // setup pins
  iocon_peripheral.Setup(pin_xtal_in, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_xtal_out, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_bootload, libmcull::iocon::PullModes::Pullup);
  iocon_peripheral.Setup(pin_debug_uart_rx, libmcull::iocon::PullModes::Pullup);
  iocon_peripheral.Setup(pin_debug_uart_tx, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_power_detect, libmcull::iocon::PullModes::Inactive, libmcuhw::iocon::PIO::HYS);
  iocon_peripheral.Setup(pin_mux1s0, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_mux1s1, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_mux1s2, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_mux2s0, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_mux2s1, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_mux2s2, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_zero_cross, libmcull::iocon::PullModes::Inactive,
                         libmcuhw::iocon::PIO::HYS | libmcuhw::iocon::PIO::IOCONCLKDIV6 | libmcuhw::iocon::PIO::CYCLES3);
  iocon_peripheral.Setup(pin_ui_button_int, libmcull::iocon::PullModes::Inactive,
                         libmcuhw::iocon::PIO::HYS | libmcuhw::iocon::PIO::IOCONCLKDIV6 | libmcuhw::iocon::PIO::CYCLES3);
  iocon_peripheral.Setup(pin_tc_amp, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_i2c_scl, libmcull::iocon::I2cModes::Standard);
  iocon_peripheral.Setup(pin_i2c_sda, libmcull::iocon::I2cModes::Standard);
  swm_periperhal.Setup(pin_xtal_in, function_xtal_in);
  swm_periperhal.Setup(pin_xtal_out, function_xtal_out);
  swm_periperhal.Setup(pin_debug_uart_rx, function_debug_uart_rx);
  swm_periperhal.Setup(pin_debug_uart_tx, function_debug_uart_tx);
  swm_periperhal.Setup(pin_tc_amp, function_adc_tc_amp);
  swm_periperhal.Setup(pin_i2c_scl, function_i2c_scl);
  swm_periperhal.Setup(pin_i2c_sda, function_i2c_sda);
  gpio_peripheral.SetInput(pin_power_detect);
  gpio_peripheral.SetInput(pin_zero_cross);
  gpio_peripheral.SetInput(pin_ui_button_int);
  gpio_peripheral.SetLow(pin_mux1s0);
  gpio_peripheral.SetLow(pin_mux1s1);
  gpio_peripheral.SetLow(pin_mux1s2);
  gpio_peripheral.SetLow(pin_mux2s0);
  gpio_peripheral.SetLow(pin_mux2s1);
  gpio_peripheral.SetLow(pin_mux2s2);
  gpio_peripheral.SetLow(pin_power_control1);
  gpio_peripheral.SetLow(pin_power_control2);
  gpio_peripheral.SetOutput(pin_mux1s0);
  gpio_peripheral.SetOutput(pin_mux1s1);
  gpio_peripheral.SetOutput(pin_mux1s2);
  gpio_peripheral.SetOutput(pin_mux2s0);
  gpio_peripheral.SetOutput(pin_mux2s1);
  gpio_peripheral.SetOutput(pin_mux2s2);
  gpio_peripheral.SetOutput(pin_power_control1);
  gpio_peripheral.SetOutput(pin_power_control2);
  // setup crystal oscillator and PLL
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  // setup systick
  systick_peripheral.Init(nuclone_clock_config.GetSystemFreq() / ticks_per_second);
  systick_peripheral.Start(systick_isr_lambda);
  // setup UART
  usart_peripheral.Init<uart_0_clock_config>(115200);
  syscon_peripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::Uart0, libmcull::syscon::ClockSources::Main);
  nvicPeripheral.Enable(libmcuhw::Interrupts::Uart0);
  // setup ADC
  // adcPeripheral.Init<diySolderClockConfig>(100000);
  // setup I2C
  i2c_peripheral.Init<i2c_0_clock_config>(400000, 100);
  syscon_peripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::I2c0, libmcull::syscon::ClockSources::Main);
  nvicPeripheral.Enable(libmcuhw::Interrupts::I2c0);
  // setup interrupt pins
  syscon_peripheral.SetInterruptPin(pin_zero_cross, zero_cross_intpin);
  pinint_peripheral.EnableChannel(zero_cross_intchan, libmcull::pin_int::EdgeSettings::Falling);
  syscon_peripheral.SetInterruptPin(pin_ui_button_int, ui_button_intpin);
  pinint_peripheral.EnableChannel(ui_button_intchan, libmcull::pin_int::EdgeSettings::Falling);
  nvicPeripheral.Enable(libmcuhw::Interrupts::Pinint0);  // todo make a nice definition for it
  nvicPeripheral.Enable(libmcuhw::Interrupts::Pinint1);
  // initialize all display devices
  // short delay for display
  while (ticks < 10)
    ;
  ui_port_expander.Init();
  ui_display.init();
  eeprom_24xxx.init();
}

void board_progress(void) {
  usart_peripheral.progress();
  i2c_peripheral.progress();
  ui_display.progress();
  ui_port_expander.progress();
  eeprom_24xxx.progress();
}

bool is_mains_present(void) {
  std::uint32_t state{gpio_peripheral.GetState(pin_power_detect)};
  return state == 1u ? true : false;
}

void set_safe_usb_powered(void) {
  set_multiplexers(0, 0);
}

void set_multiplexers(std::uint32_t mux1, std::uint32_t mux2) {
  uint32_t mask{pin_mux1s0.gpioPinMask | pin_mux1s1.gpioPinMask | pin_mux1s2.gpioPinMask | pin_mux2s0.gpioPinMask |
                pin_mux2s1.gpioPinMask | pin_mux2s2.gpioPinMask};
  // clamp mux values
  mux1 = mux1 & 0x7;
  mux2 = mux2 & 0x7;
  uint32_t portValue{(mux1 << pin_mux1s0.gpioPinIndex) | (mux2 << pin_mux2s0.gpioPinIndex)};
  gpio_peripheral.SetPort(port_mux, portValue, mask);
}

void set_power_control_1(bool on) {
  gpio_peripheral.SetState(pin_power_control1, !on);
}

void set_power_control_2(bool on) {
  gpio_peripheral.SetState(pin_power_control2, !on);
}