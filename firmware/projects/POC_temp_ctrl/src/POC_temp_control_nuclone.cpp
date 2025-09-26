/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#include <POC_temp_control_nuclone.hpp>
#include <application.hpp>

libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
libmcull::systick::Systick<libmcuhw::SystickAddress> systick_peripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvicPeripheral;
libmcull::adc::Adc<libmcuhw::Adc0Address> adc_peripheral;
libmcull::pin_int::Pinint<libmcuhw::PinintAddress> pinint_peripheral;
libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 128> ll_usart_peripheral;

libmcuhal::usart::UartInterrupt<ll_usart_peripheral, char> usart_peripheral;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systick_peripheral.Isr();
}

void USART0_IRQHandler(void) {
  ll_usart_peripheral.InterruptHandler();
}

void PIN_INT0_IRQHandler(void) {
  pinint_peripheral.ClearChannel(libmcull::pin_int::InterruptPins::PintSel0);
  application::zerocross.Update();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
};

void BoardInit(void) {
  ticks = 0;
  // clock, power and reset enables/clears
  syscon_peripheral.PowerPeripherals(libmcull::syscon::power_options::SysOsc | libmcull::syscon::power_options::Adc);
  syscon_peripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::Uart0 | libmcull::syscon::peripheral_clocks_0::Adc |
      libmcull::syscon::peripheral_clocks_0::GpioInt,
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
  iocon_peripheral.Setup(pin_tc_amp, libmcull::iocon::PullModes::Inactive);
  swm_periperhal.Setup(pin_xtal_in, function_xtal_in);
  swm_periperhal.Setup(pin_xtal_out, function_xtal_out);
  swm_periperhal.Setup(pin_debug_uart_rx, function_debug_uart_rx);
  swm_periperhal.Setup(pin_debug_uart_tx, function_debug_uart_tx);
  swm_periperhal.Setup(pin_tc_amp, function_adc_tc_amp);
  gpio_peripheral.SetInput(pin_power_detect);
  gpio_peripheral.SetInput(pin_zero_cross);
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
  systick_peripheral.Start(systickIsrLambda);
  // setup UART
  usart_peripheral.Init<uart_0_clock_config>(115200);
  syscon_peripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::Uart0, libmcull::syscon::ClockSources::Main);
  nvicPeripheral.Enable(libmcuhw::Interrupts::Uart0);
  nvicPeripheral.Enable(libmcuhw::Interrupts::Pinint0);
  // setup ADC
  // adcPeripheral.Init<diySolderClockConfig>(100000);
  // setup interrupt pin
  syscon_peripheral.SetInterruptPin(pin_zero_cross, libmcull::syscon::InterruptPins::PintSel0);
  pinint_peripheral.EnableChannel(libmcull::pin_int::InterruptPins::PintSel0, libmcull::pin_int::EdgeSettings::Falling);
}

bool IsMainsPresent(void) {
  std::uint32_t state{gpio_peripheral.GetState(pin_power_detect)};
  return state == 1u ? true : false;
}

void SetSafeUsbPowered(void) {
  SetMultiplexers(0, 0);
}

void SetMultiplexers(std::uint32_t mux1, std::uint32_t mux2) {
  uint32_t mask{pin_mux1s0.gpioPinMask | pin_mux1s1.gpioPinMask | pin_mux1s2.gpioPinMask | pin_mux2s0.gpioPinMask |
                pin_mux2s1.gpioPinMask | pin_mux2s2.gpioPinMask};
  // clamp mux values
  mux1 = mux1 & 0x7;
  mux2 = mux2 & 0x7;
  uint32_t portValue{(mux1 << pin_mux1s0.gpioPinIndex) | (mux2 << pin_mux2s0.gpioPinIndex)};
  gpio_peripheral.SetPort(port_mux, portValue, mask);
}

void SetPowerControl1(bool on) {
  gpio_peripheral.SetState(pin_power_control1, on);
}

void SetPowerControl2(bool on) {
  gpio_peripheral.SetState(pin_power_control2, on);
}