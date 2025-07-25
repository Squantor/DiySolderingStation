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

libmcull::iocon::Iocon<libmcuhw::kIoconAddress> ioconPeripheral;
libmcull::swm::Swm<libmcuhw::kSwmAddress> swmPeriperhal;
libmcull::gpio::Gpio<libmcuhw::kGpioAddress> gpioPeripheral;
libmcull::syscon::Syscon<libmcuhw::kSysconAddress> sysconPeripheral;
libmcull::systick::Systick<libmcuhw::kSystickAddress> systickPeripheral;
libmcull::nvic::Nvic<libmcuhw::kNvicAddress, libmcuhw::kScbAddress> nvicPeripheral;
libmcuhal::usart::UartInterrupt<char, 128> usartPeripheral;
libmcull::adc::Adc<libmcuhw::kAdc0Address> adcPeripheral;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.isr();
}

void USART0_IRQHandler(void) {
  // usartPeripheral.isr();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
};

void boardInit(void) {
  ticks = 0;
  // clock, power and reset enables/clears
  sysconPeripheral.PowerPeripherals(libmcull::syscon::power_options::SysOsc | libmcull::syscon::power_options::Adc);
  sysconPeripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::Uart0 | libmcull::syscon::peripheral_clocks_0::Adc,
    0);
  // setup pins
  ioconPeripheral.Setup(xtalInPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(xtalOutPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(bootloadPin, libmcull::iocon::PullModes::Pullup);
  ioconPeripheral.Setup(debugUartRxPin, libmcull::iocon::PullModes::Pullup);
  ioconPeripheral.Setup(debugUartTxPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(PowerDetectPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(mux1s0Pin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(mux1s1Pin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(mux1s2Pin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(mux2s0Pin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(mux2s1Pin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(mux2s2Pin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(TcAmpPin, libmcull::iocon::PullModes::Inactive);
  swmPeriperhal.Setup(xtalInPin, xtalInFunction);
  swmPeriperhal.Setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.Setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.Setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.Setup(TcAmpPin, adcTcAmpFunction);
  gpioPeripheral.SetInput(PowerDetectPin);
  gpioPeripheral.SetLow(mux1s0Pin);
  gpioPeripheral.SetLow(mux1s1Pin);
  gpioPeripheral.SetLow(mux1s2Pin);
  gpioPeripheral.SetLow(mux2s0Pin);
  gpioPeripheral.SetLow(mux2s1Pin);
  gpioPeripheral.SetLow(mux2s2Pin);
  gpioPeripheral.SetOutput(mux1s0Pin);
  gpioPeripheral.SetOutput(mux1s1Pin);
  gpioPeripheral.SetOutput(mux1s2Pin);
  gpioPeripheral.SetOutput(mux2s0Pin);
  gpioPeripheral.SetOutput(mux2s1Pin);
  gpioPeripheral.SetOutput(mux2s2Pin);
  // setup crystal oscillator
  // libmcuhw::clock::configureClocks<sysconPeripheral, diySolderClockConfig>();
  // setup systick
  // systickPeripheral.init(diySolderClockConfig.systemFreq / TICKS_PER_S);
  systickPeripheral.start(systickIsrLambda);
  // setup UART
  sysconPeripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::Uart0, libmcull::syscon::ClockSources::Main);
  // usartPeripheral.init<diySolderClockConfig>(115200);
  nvicPeripheral.enable(libmcuhw::Interrupts::kUart0);
  // setup ADC
  // adcPeripheral.Init<diySolderClockConfig>(100000);
}

bool isMainsPresent(void) {
  std::uint32_t state{gpioPeripheral.GetState(PowerDetectPin)};
  return state == 1u ? true : false;
}

void setSafeUsbPowered(void) {
  setMultiplexers(0, 0);
}

void setMultiplexers(std::uint32_t mux1, std::uint32_t mux2) {
  uint32_t mask{mux1s0Pin.gpioPinMask | mux1s1Pin.gpioPinMask | mux1s2Pin.gpioPinMask | mux2s0Pin.gpioPinMask |
                mux2s1Pin.gpioPinMask | mux2s2Pin.gpioPinMask};
  // clamp mux values
  mux1 = mux1 & 0x7;
  mux2 = mux2 & 0x7;
  uint32_t portValue{(mux1 << mux1s0Pin.gpioPinIndex) | (mux2 << mux2s0Pin.gpioPinIndex)};
  gpioPeripheral.SetPort(muxPort, portValue, mask);
}