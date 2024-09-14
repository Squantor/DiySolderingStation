/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#include <POC_temp_sense_nuclone.hpp>

libMcu::ll::iocon::iocon<libMcu::hw::ioconAddress> ioconPeripheral;
libMcu::ll::swm::swm<libMcu::hw::swmAddress> swmPeriperhal;
libMcu::ll::gpio::gpio<libMcu::hw::gpioAddress> gpioPeripheral;
libMcu::ll::syscon::syscon<libMcu::hw::sysconAddress> sysconPeripheral;
libMcu::ll::systick::systick<libMcu::hw::systickAddress> systickPeripheral;
libMcu::ll::nvic::nvic<libMcu::hw::nvicAddress, libMcu::hw::scbAddress> nvicPeripheral;
libMcu::hal::usart::uartSync<libMcu::hw::usart0Address, libMcu::hw::nvicAddress, char, 128> usartPeripheral;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.isr();
}

void USART0_IRQHandler(void) {
  usartPeripheral.isr();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
};

void boardInit(void) {
  ticks = 0;
  // clock enables and resets
  sysconPeripheral.enablePeripheralClocks(
    libMcu::ll::syscon::peripheralClocks0::SWM | libMcu::ll::syscon::peripheralClocks0::IOCON |
      libMcu::ll::syscon::peripheralClocks0::GPIO0 | libMcu::ll::syscon::peripheralClocks0::GPIO1 |
      libMcu::ll::syscon::peripheralClocks0::UART0,
    0);
  // setup pins
  ioconPeripheral.setup(xtalInPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(bootloadPin, libMcu::ll::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartRxPin, libMcu::ll::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartTxPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(PowerDetectPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux1s0Pin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux1s1Pin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux1s2Pin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux2s0Pin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux2s1Pin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux2s2Pin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(diffAmpInputPin, libMcu::ll::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.setup(debugUartTxPin, uartDebugTxFunction);
  gpioPeripheral.input(PowerDetectPin);
  gpioPeripheral.low(mux1s0Pin);
  gpioPeripheral.low(mux1s1Pin);
  gpioPeripheral.low(mux1s2Pin);
  gpioPeripheral.low(mux2s0Pin);
  gpioPeripheral.low(mux2s1Pin);
  gpioPeripheral.low(mux2s2Pin);
  gpioPeripheral.output(mux1s0Pin);
  gpioPeripheral.output(mux1s1Pin);
  gpioPeripheral.output(mux1s2Pin);
  gpioPeripheral.output(mux2s0Pin);
  gpioPeripheral.output(mux2s1Pin);
  gpioPeripheral.output(mux2s2Pin);
  // setup crystal oscillator
  sysconPeripheral.setSysOscControl(libMcu::hw::syscon::SYSOSCCTRL::NO_BYPASS | libMcu::hw::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  sysconPeripheral.powerPeripherals(libMcu::ll::syscon::powerOptions::SYSOSC);
  libMcu::sw::delay(3000);
  // setup PLL
  sysconPeripheral.selectPllClock(libMcu::ll::syscon::pllClockSources::EXT);
  sysconPeripheral.depowerPeripherals(libMcu::ll::syscon::powerOptions::SYSPLL);
  sysconPeripheral.setSystemPllControl(4, libMcu::ll::syscon::pllPostDivider::DIV_4);
  sysconPeripheral.powerPeripherals(libMcu::ll::syscon::powerOptions::SYSPLL);
  while (sysconPeripheral.getSystemPllStatus() == 0)
    ;
  sysconPeripheral.setSystemClockDivider(2);
  // switch mainclock
  sysconPeripheral.selectMainPllClock(libMcu::ll::syscon::mainClockPllSources::SYSPLL);
  // setup systick
  systickPeripheral.init(CLOCK_CPU / TICKS_PER_S);
  systickPeripheral.start(systickIsrLambda);
  // setup UART
  sysconPeripheral.peripheralClockSource(libMcu::ll::syscon::clockSourceSelects::UART0, libMcu::ll::syscon::clockSources::MAIN);
  usartPeripheral.init(115200);
  nvicPeripheral.enable(libMcu::hw::interrupts::uart0);
}

bool isMainsPresent(void) {
  std::uint32_t state{gpioPeripheral.get(PowerDetectPin)};
  return state == 1u ? true : false;
}