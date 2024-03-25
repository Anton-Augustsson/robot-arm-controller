#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef SIMULATION_ENABLED
#include "src/simulation/mock.hpp"
#define LOOP int i = 0; i < 10; i++
#else
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#define LOOP ;;
#endif

#include "src/motor/servo_motor.hpp" 
#include "src/motor/mg996r.hpp" 
#include "src/utils/types.hpp" 

#define LED_PIN 25
#define BUF_LEN 32
#define MAX_DUTY_CYCLE 65535 // 2^16-1
#define PWM_FREQUENCY 2500 // 50 Hz (2500 us period)

void printbuf(uint8_t buf[], size_t len) {
  int i;
  for (i = 0; i < len; i++) {
    // If last message in buffer
    if (i % 16 == 15)
      printf("%02x\n", buf[i]);
    else
      printf("%02x", buf[i]);

  }
}

int main () {
  // Binary Information 
  bi_decl(bi_program_description("Sample binary"));
  bi_decl(bi_1pin_with_name(LED_PIN, "on-board PIN"));

  //MotorParameters motorParameters0 = {"mg996r", 0, PwmRange {3, 12}, AngleRange {0, 90}};
  //Mg996r motor0 = Mg996r(motorParameters0);

  // Enable UART so we can print
  stdio_init_all();

  // Setup LED pin
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  // Setup PWM pin
  gpio_set_function(2, GPIO_FUNC_PWM);

  // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
  uint8_t slice_num = pwm_gpio_to_slice_num(2);
  pwm_set_clkdiv(slice_num, PWM_FREQUENCY); 
  pwm_set_wrap(slice_num, MAX_DUTY_CYCLE);
  // Set the PWM running
  pwm_set_enabled(slice_num, true);
  // Set PWM duty cycle
  uint16_t duty_cycle = MAX_DUTY_CYCLE*0.004;
  pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);

  // Just for debuging reasons
  sleep_ms(2 * 1000);
  printf("SPI Peripheral Example\n");

  // Set PWM duty cycle
  duty_cycle = MAX_DUTY_CYCLE*0.01;
  pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);

  // Enable SPI 0 at 1 MHz and connect to GPIOs
  spi_init(spi_default, 1 * 1000000);
  spi_set_slave(spi_default, true);
  gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
  // Make the SPI pins available to picotool
  //bi_decl(bi_4pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI));

  uint8_t out_buf [BUF_LEN], in_buf [BUF_LEN];

  // Initialize output buffer
  for (uint8_t i = 0; i < BUF_LEN; ++i) {
    out_buf[i] = 2;
    in_buf[i] = 0;
  }

  for(LOOP) {
    gpio_put(LED_PIN, 0);

    if (spi_is_readable (spi_default)) {
      printf("Reading data from SPI..\n");
      gpio_put(LED_PIN, 1);

      // Write the output buffer to MOSI, and at the same time read from MISO.
      spi_write_read_blocking(spi_default, out_buf, in_buf, 1);
      //spi_read_blocking(spi_default, 0, in_buf, 1);

      printf ("Data received: ");// %d\n", in_buf[0]);
      printbuf(in_buf, BUF_LEN);
    }
  }
}
