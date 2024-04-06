#include "sim_context_singleton.hpp"

std::string statusSpiToString(Status_spi status) {
  switch (status) {
    case Status_spi::UNINITIALIZED:
        return "Uninitialized";
    case Status_spi::INITIALIZED:
        return "Initialized";
    case Status_spi::READY:
        return "Ready";
    case Status_spi::ERROR:
        return "Error";
    default:
        return "Unknown";
  }
}

std::string statusPwmToString(Status_pwm status) {
  switch (status) {
    case Status_pwm::UNINITIALIZED:
      return "Uninitialized";
    case Status_pwm::CLKDIV_SET:
      return "clkdiv is set";
    case Status_pwm::WRAP_SET:
      return "wrap is set";
    case Status_pwm::ENABLED:
      return "Enabled";
    case Status_pwm::CHAN_LEVEL_SET:
      return "Chanel level set";
    case Status_pwm::ERROR:
      return "Error";
    default:
      return "Unknown";
  }
}

std::string statusGpioToString(Status_gpio status) {
  switch (status) {
    case Status_gpio::UNINITIALIZED:
      return "Uninitialized";
    case Status_gpio::INITIALIZED:
      return "Initialized";
    case Status_gpio::LED_READY:
      return "LED Ready";
    case Status_gpio::PWM_READY:
      return "PWM Ready";
    case Status_gpio::ERROR:
      return "Error";
    default:
      return "Unknown";
  }
}

SimContextSingleton* SimContextSingleton::singleton_= nullptr;;
motor *SimContextSingleton::pwmMotors[6] = {nullptr};

SimContextSingleton *SimContextSingleton::GetInstance() {
  if(singleton_==nullptr) {
      singleton_ = new SimContextSingleton();
  }
  return singleton_;
}

SimContextSingleton::~SimContextSingleton() {
    for (motor *m : pwmMotors) {
        delete m;
    }
    delete singleton_;
}

void SimContextSingleton::initMotors() {
  if(pwmMotors[0] == nullptr) {
    pwmMotors[0] = new motor();
    pwmMotors[1] = new motor();
    pwmMotors[2] = new motor();
    pwmMotors[3] = new motor();
    pwmMotors[4] = new motor();
    pwmMotors[5] = new motor();

    pwmMotors[0]->id = motor_id_t::m0;
    pwmMotors[1]->id = motor_id_t::m1;
    pwmMotors[2]->id = motor_id_t::m2;
    pwmMotors[3]->id = motor_id_t::m3;
    pwmMotors[4]->id = motor_id_t::m4;
    pwmMotors[5]->id = motor_id_t::m5;

    pwmMotors[0]->gpio_or_slice_num = 2;
    pwmMotors[1]->gpio_or_slice_num = 3;
    pwmMotors[2]->gpio_or_slice_num = 4;
    pwmMotors[3]->gpio_or_slice_num = 6;
    pwmMotors[4]->gpio_or_slice_num = 7;
    pwmMotors[5]->gpio_or_slice_num = 8;

    for (motor *m : pwmMotors) {
      m->status = Status_pwm::UNINITIALIZED;
    }
  }
}

void SimContextSingleton::setSpiStatus(Status_spi status) {
  spiPeripheral = status;
}

void SimContextSingleton::setGpioStatus(led_id_t id, Status_gpio status) {
  // TODO: gind gpio id
  gpioLed.status = status;
}

void SimContextSingleton::setMotorStatus(motor_id_t id, Status_pwm status) {
  for (motor *m : pwmMotors) {
    if (m->id == id) {
      m->status = status;
      break;
    }
  }
}

void SimContextSingleton::setMotorStatus(unsigned int gpio_or_slice_num, Status_pwm status) {
  for (motor *m : pwmMotors) {
    if (m->gpio_or_slice_num == gpio_or_slice_num) {
      m->status = status;
      break;
    }
  }
}

Status_spi SimContextSingleton::getSpiStatus() {
  return spiPeripheral;
}

Status_gpio SimContextSingleton::getGpioStatus(led_id_t id) {
  // TODO: gind gpio id
  return gpioLed.status;
}

Status_pwm SimContextSingleton::getMotorStatus(motor_id_t id) {
  for (motor *m : pwmMotors) {
    if (m->id == id) {
      return m->status;
    }
  }
  return Status_pwm::ERROR;
}

Status_pwm SimContextSingleton::getMotorStatus(unsigned int gpio_or_slice_num) {
  for (motor *m : pwmMotors) {
    if (m->gpio_or_slice_num == gpio_or_slice_num) {
      return m->status;
    }
  }
  return Status_pwm::ERROR;
}
