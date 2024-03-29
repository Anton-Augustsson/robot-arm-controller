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

std::string statusPwdToString(Status_pwm status) {
  switch (status) {
    case Status_pwm::UNINITIALIZED:
      return "Uninitialized";
    case Status_pwm::INITIALIZED:
      return "Initialized";
    case Status_pwm::READY:
      return "Ready";
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

SimContextSingleton *SimContextSingleton::GetInstance(const std::string& value) {
  if(singleton_==nullptr) {
      singleton_ = new SimContextSingleton(value);
  }
  return singleton_;
}

void SimContextSingleton::setSpiStatus(Status_spi status) {
  spiPeripheral = status;
}

void SimContextSingleton::setMotorStatus(motor_id_t id, Status_pwm status) {
  for (motor m : pwmMotors) {
    if (m.id == id) {
      m.status = status;
      break;
    }
  }
}

Status_spi SimContextSingleton::getSpiStatus() {
  return spiPeripheral;
}

Status_pwm SimContextSingleton::getMotorStatus(motor_id_t id) {
  for (motor m : pwmMotors) {
    if (m.id == id) {
      return m.status;
    }
  }
  return Status_pwm::ERROR;
}
