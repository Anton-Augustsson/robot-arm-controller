#ifndef SIM_CONTEXT_SINGELTON_HPP
#define SIM_CONTEXT_SINGELTON_HPP

#include <stdio.h>
#include <string.h>
#include "../utils/types.hpp"

enum class Status_spi { UNINITIALIZED, INITIALIZED, READY, ERROR };
enum class Status_pwm { UNINITIALIZED, INITIALIZED, READY, ERROR };
enum class Status_gpio { UNINITIALIZED, INITIALIZED, LED_READY, PWM_READY, ERROR };

std::string statusSpiToString(Status_spi status);
std::string statusPwdToString(Status_pwm status);
std::string statusGpioToString(Status_gpio status);

struct motor {
  motor_id_t id;
  Status_pwm status;
};

struct led {
  led_id_t id;
  Status_gpio status;
};

class SimContextSingleton {
  protected:
    SimContextSingleton(const std::string value) {
      gpioLed.status = Status_gpio::UNINITIALIZED;
      spiPeripheral = Status_spi::UNINITIALIZED;
      value_ = value;
      for (motor m : pwmMotors) {
        m.status = Status_pwm::UNINITIALIZED;
      }
      pwmMotors[0].id = motor_id_t::m1;
      pwmMotors[1].id = motor_id_t::m2;
      pwmMotors[2].id = motor_id_t::m3;
      pwmMotors[3].id = motor_id_t::m4;
      pwmMotors[4].id = motor_id_t::m5;

    }
    static SimContextSingleton* singleton_;

    led gpioLed;
    motor pwmMotors[5];
    Status_spi spiPeripheral;
    std::string value_;

  public:
    SimContextSingleton(SimContextSingleton &other) = delete;
    void operator=(const SimContextSingleton &) = delete;
    static SimContextSingleton *GetInstance(const std::string& value);

    void setSpiStatus(Status_spi status);
    void setLedStatus(led_id_t id, Status_gpio status);
    void setMotorStatus(motor_id_t id, Status_pwm status);

    Status_spi getSpiStatus();
    Status_pwm getMotorStatus(motor_id_t id);

    std::string value() const{
        return value_;
    } 
};



#endif