#include <iostream>
#include <cassert>
#include "mock.hpp"
#include "../simulation/sim_context_singleton.hpp" 

void printSpiStatus(unsigned int gpio) {
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  std::cout << "SPI GPIO " << gpio << " " << statusSpiToString(simContext->getSpiStatus()) << std::endl;
}

void spi_init(unsigned int gpio, unsigned int frequency) {
  // TODO: check that it is the correct gpio
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  simContext->setSpiStatus(Status_spi::INITIALIZED);
  printSpiStatus(gpio);
}

void spi_set_slave(unsigned int gpio, bool enable) {
  // TODO: check that it is the correct gpio
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  assert(simContext->getSpiStatus() == Status_spi::INITIALIZED);
  simContext->setSpiStatus(Status_spi::READY);
  printSpiStatus(gpio);
}

void spi_write_read_blocking(unsigned int gpio, uint8_t *out_buf, uint8_t *in_buf, unsigned int buf_read) {
  // TODO: check that it is the correct gpio
  // TODO: read some from file? So to test the driver you can write to file
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  assert(simContext->getSpiStatus() == Status_spi::READY);
  return;
}


bool spi_is_readable(unsigned int gpio) {
  // TODO: if a file is used to communicate then check if it has been writen to
  return false;
}
