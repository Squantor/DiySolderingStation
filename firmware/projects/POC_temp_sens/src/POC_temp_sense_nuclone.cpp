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

libMcuLL::iocon::iocon<libMcuLL::hw::ioconAddress> ioconPeripheral;
libMcuLL::swm::swm<libMcuLL::hw::swmAddress> swmPeriperhal;
libMcuLL::gpio::gpio<libMcuLL::hw::gpioAddress> gpioPeripheral;
libMcuLL::syscon::syscon<libMcuLL::hw::sysconAddress> sysconPeripheral;
libMcuLL::systick::systick<libMcuLL::hw::systickAddress> systickPeripheral;
libMcuLL::nvic::nvic<libMcuLL::hw::nvicAddress, libMcuLL::hw::scbAddress> nvicPeripheral;
libMcuHal::usart::uartSync<libMcuLL::hw::usart0Address, libMcuLL::hw::nvicAddress, char, 128> usartPeripheral;

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
  sysconPeripheral.enablePeripheralClocks(libMcuLL::syscon::peripheralClocks0::SWM | libMcuLL::syscon::peripheralClocks0::IOCON |
                                            libMcuLL::syscon::peripheralClocks0::GPIO0 |
                                            libMcuLL::syscon::peripheralClocks0::GPIO1 | libMcuLL::syscon::peripheralClocks0::UART0,
                                          0);
  // setup pins
  ioconPeripheral.setup(xtalInPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(bootloadPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartRxPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartTxPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(PowerDetectPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux1s0Pin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux1s1Pin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux1s2Pin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux2s0Pin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux2s1Pin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(mux2s2Pin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(diffAmpInputPin, libMcuLL::iocon::pullModes::INACTIVE);
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
  sysconPeripheral.setSysOscControl(libMcuLL::hw::syscon::SYSOSCCTRL::NO_BYPASS | libMcuLL::hw::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  sysconPeripheral.powerPeripherals(libMcuLL::syscon::powerOptions::SYSOSC);
  libMcu::sw::delay(3000);
  // setup PLL
  sysconPeripheral.selectPllClock(libMcuLL::syscon::pllClockSources::EXT);
  sysconPeripheral.depowerPeripherals(libMcuLL::syscon::powerOptions::SYSPLL);
  sysconPeripheral.setSystemPllControl(4, libMcuLL::syscon::pllPostDivider::DIV_4);
  sysconPeripheral.powerPeripherals(libMcuLL::syscon::powerOptions::SYSPLL);
  while (sysconPeripheral.getSystemPllStatus() == 0)
    ;
  sysconPeripheral.setSystemClockDivider(2);
  // switch mainclock
  sysconPeripheral.selectMainPllClock(libMcuLL::syscon::mainClockPllSources::SYSPLL);
  // setup systick
  systickPeripheral.init(CLOCK_CPU / TICKS_PER_S);
  systickPeripheral.start(systickIsrLambda);
  // setup UART
  sysconPeripheral.peripheralClockSource(libMcuLL::syscon::clockSourceSelects::UART0, libMcuLL::syscon::clockSources::MAIN);
  usartPeripheral.init(115200);
  nvicPeripheral.enable(libMcuLL::hw::interrupts::uart0);
}

bool isMainsPresent(void) {
  std::uint32_t state{gpioPeripheral.get(PowerDetectPin)};
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
  gpioPeripheral.portSet(muxPort, portValue, mask);
}