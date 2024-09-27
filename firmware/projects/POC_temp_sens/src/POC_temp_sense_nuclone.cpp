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

libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
libMcuLL::syscon::syscon<libMcuHw::sysconAddress> sysconPeripheral;
libMcuLL::systick::systick<libMcuHw::systickAddress> systickPeripheral;
libMcuLL::nvic::nvic<libMcuHw::nvicAddress, libMcuHw::scbAddress> nvicPeripheral;
libMcuHal::usart::uartSync<libMcuHw::usart0Address, libMcuHw::nvicAddress, char, 128> usartPeripheral;
libMcuLL::adc::adc<libMcuHw::adc0Address> adcPeripheral;

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
  // clock, power and reset enables/clears
  sysconPeripheral.powerPeripherals(libMcuLL::syscon::powerOptions::SYSOSC | libMcuLL::syscon::powerOptions::ADC);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::syscon::peripheralClocks0::SWM | libMcuLL::syscon::peripheralClocks0::IOCON |
                                            libMcuLL::syscon::peripheralClocks0::GPIO0 |
                                            libMcuLL::syscon::peripheralClocks0::GPIO1 |
                                            libMcuLL::syscon::peripheralClocks0::UART0 | libMcuLL::syscon::peripheralClocks0::ADC,
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
  ioconPeripheral.setup(TcAmpPin, libMcuLL::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.setup(TcAmpPin, adcTcAmpFunction);
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
  sysconPeripheral.setSysOscControl(libMcuHw::syscon::SYSOSCCTRL::NO_BYPASS | libMcuHw::syscon::SYSOSCCTRL::FREQ_1_20MHz);

  libMcuLL::adc::adc<libMcuHw::adc0Address> adcPeripheral;
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
  nvicPeripheral.enable(libMcuHw::interrupts::uart0);
  // setup ADC
  adcPeripheral.init(1200000);
  adcPeripheral.sample(TcAmpPin);
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