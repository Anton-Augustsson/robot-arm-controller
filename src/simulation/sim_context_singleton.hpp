#ifndef SIM_CONTEXT_SINGELTON_HPP
#define SIM_CONTEXT_SINGELTON_HPP

#include <stdio.h>
#include <string.h>
#include "../utils/types.hpp"

enum class Status_spi { UNINITIALIZED, INITIALIZED, READY, ERROR };
enum class Status_pwm { UNINITIALIZED, CLKDIV_SET, WRAP_SET, ENABLED, CHAN_LEVEL_SET, ERROR };
enum class Status_gpio { UNINITIALIZED, INITIALIZED, LED_READY, PWM_READY, ERROR };

std::string statusSpiToString(Status_spi status);
std::string statusPwmToString(Status_pwm status);
std::string statusGpioToString(Status_gpio status);

struct motor {
  motor_id_t id;
  unsigned int gpio_or_slice_num;
  Status_pwm status;
};

struct led {
  led_id_t id;
  Status_gpio status;
};

class SimContextSingleton {
  protected:
    SimContextSingleton() {
      gpioLed.status = Status_gpio::UNINITIALIZED;
      spiPeripheral = Status_spi::UNINITIALIZED;
      initMotors();
    }
    static SimContextSingleton* singleton_;

    led gpioLed;
    Status_spi spiPeripheral;
    static motor *pwmMotors[5];

    void initMotors();
    void destroyMotors();

  public:
    SimContextSingleton(SimContextSingleton &other) = delete;
    ~SimContextSingleton();
    void operator=(const SimContextSingleton &) = delete;
    static SimContextSingleton *GetInstance();

    void setSpiStatus(Status_spi status);
    void setGpioStatus(led_id_t id, Status_gpio status);
    void setMotorStatus(motor_id_t id, Status_pwm status);
    void setMotorStatus(unsigned int gpio_or_slice_num, Status_pwm status);

    Status_spi getSpiStatus();
    Status_gpio getGpioStatus(led_id_t id);
    Status_pwm getMotorStatus(motor_id_t id);
    Status_pwm getMotorStatus(unsigned int gpio_or_slice_num);
};


#endif