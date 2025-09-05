/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief code for LPC845 small nuclone LL tester
 */
#include <nuclone_LPC845BD48_small.hpp>

libMcu::ll::iocon::iocon<libMcu::hw::ioconAddress> ioconPeripheral;
libMcu::ll::swm::swm<libMcu::hw::swmAddress> swmPeriperhal;
libMcu::ll::gpio::gpio<libMcu::hw::gpioAddress> gpioPeripheral;
libMcu::ll::syscon::syscon<libMcu::hw::sysconAddress> syscon_peripheral;
libMcu::ll::usart::usart<libMcu::hw::usart0Address, std::uint8_t> usart_peripheral;

void boardInit(void) {
  // clock enables and resets
  syscon_peripheral.enablePeripheralClocks(
    libMcu::ll::syscon::peripheralClocks0::SWM | libMcu::ll::syscon::peripheralClocks0::IOCON |
      libMcu::ll::syscon::peripheralClocks0::GPIO0 | libMcu::ll::syscon::peripheralClocks0::GPIO1,
    0);
  // setup IOCON pins
  ioconPeripheral.setup(xtalInPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcu::ll::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  // setup crystal oscillator
  syscon_peripheral.setSysOscControl(libMcu::hw::syscon::SYSOSCCTRL::NO_BYPASS | libMcu::hw::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  syscon_peripheral.powerPeripherals(libMcu::ll::syscon::powerOptions::SYSOSC);
  libMcu::sw::delay(3000);
  // setup PLL
  syscon_peripheral.selectPllClock(libMcu::ll::syscon::pllClockSources::EXT);
  syscon_peripheral.depowerPeripherals(libMcu::ll::syscon::powerOptions::SYSPLL);
  syscon_peripheral.setSystemPllControl(4, libMcu::ll::syscon::pllPostDivider::DIV_4);
  syscon_peripheral.powerPeripherals(libMcu::ll::syscon::powerOptions::SYSPLL);
  while (syscon_peripheral.getSystemPllStatus() == 0)
    ;
  syscon_peripheral.setSystemClockDivider(2);
  // switch mainclock
  // syscon_peripheral.selectMainClock(libMcu::ll::syscon::mainClockSources::EXT); // for selecting crystal oscillator
  syscon_peripheral.selectMainPllClock(libMcu::ll::syscon::mainClockPllSources::SYSPLL);
  // setup clock out test pin
  swmPeriperhal.setup(testPin, clockOutFunction);
  // setup clock output
  syscon_peripheral.setClockOutput(libMcu::ll::syscon::clockOutSources::MAIN, 10u);
}
