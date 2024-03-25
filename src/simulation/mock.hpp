#ifndef Mocks_HPP
#define Mock_HPP

#include <stdint.h>
#include <string>

#define GPIO_OUT 1
#define PWM_CHAN_A 1
#define PICO_DEFAULT_SPI_TX_PIN 1
#define PICO_DEFAULT_SPI_RX_PIN 1
#define PICO_DEFAULT_SPI_SCK_PIN 1
#define PICO_DEFAULT_SPI_CSN_PIN 1

const unsigned int spi_default = 1;

enum gpio_function {
    GPIO_FUNC_INPUT = 0,
    GPIO_FUNC_OUTPUT = 1,
    GPIO_FUNC_SPI = 2,
    GPIO_FUNC_I2C = 3,
    GPIO_FUNC_PWM = 4,
};

void bi_decl(void *);
void *bi_program_description(std::string desc);
void *bi_1pin_with_name(unsigned int gpio, std::string name);

void stdio_init_all();
void sleep_ms(unsigned int time);

void gpio_init(unsigned int gpio);
void gpio_set_dir(unsigned int gpio, bool out);
void gpio_set_function(unsigned int gpio, enum gpio_function fn); // Or unsigned int
void gpio_put(unsigned int gpio, unsigned int value);

void pwm_set_clkdiv(unsigned int slice_num, float divider);
void pwm_set_wrap(unsigned int slice_num, int wrap);
unsigned int pwm_gpio_to_slice_num(unsigned int gpio);
void pwm_set_enabled(unsigned int slice_num, bool enable);
void pwm_set_chan_level(unsigned int slice_num, unsigned int chan, int level);

void spi_init(unsigned int gpio, unsigned int frequency);
void spi_set_slave(unsigned int gpio, bool enable);
void spi_write_read_blocking(unsigned int gpio, uint8_t *out_buf, uint8_t *in_buf, unsigned int buf_read);
bool spi_is_readable(unsigned int gpio);


#endif