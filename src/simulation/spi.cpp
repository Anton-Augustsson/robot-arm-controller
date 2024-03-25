#include "mock.hpp"

void spi_init(unsigned int gpio, unsigned int frequency) {
  return;
}

void spi_set_slave(unsigned int gpio, bool enable) {
  return;
}

void spi_write_read_blocking(unsigned int gpio, uint8_t *out_buf, uint8_t *in_buf, unsigned int buf_read) {
  return;
}


bool spi_is_readable(unsigned int gpio) {
  return false;
}
