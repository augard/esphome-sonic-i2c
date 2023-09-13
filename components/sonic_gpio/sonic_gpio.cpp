#include "sonic_gpio.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sonic_gpio {

static const char *const TAG = "sonicgpio.sensor";

void SonicGPIOComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Sonic GPIO Sensor...");
  pinMode(26, OUTPUT);
  pinMode(32, INPUT);
}
void SonicGPIOComponent::update() {
  digitalWrite(26, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds.

  digitalWrite(26, HIGH);
  delayMicroseconds(10);
  digitalWrite(26, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(32, HIGH);
  float result = duration * 0.34 / 2;
  if (result > 4500) {
    result = 4500;
  }

  if (result <= 0) {
    ESP_LOGD(TAG, "'%s' - Distance measurement timed out!", this->name_.c_str());
    this->publish_state(NAN);
  } else {
    ESP_LOGD(TAG, "'%s' - Got distance: %.2f m", this->name_.c_str(), result);
    this->publish_state(result);
  }
}
void SonicGPIOComponent::dump_config() {
  LOG_SENSOR("", "Ultrasonic Sensor", this);
  LOG_PIN("  Echo Pin: ", this->echo_pin_);
  LOG_PIN("  Trigger Pin: ", this->trigger_pin_);
  ESP_LOGCONFIG(TAG, "  Pulse time: %u µs", this->pulse_time_us_);
  ESP_LOGCONFIG(TAG, "  Timeout: %u µs", this->timeout_us_);
  LOG_UPDATE_INTERVAL(this);
}
float SonicGPIOComponent::get_setup_priority() const { return setup_priority::DATA; }
void SonicGPIOComponent::set_pulse_time_us(uint32_t pulse_time_us) { this->pulse_time_us_ = pulse_time_us; }
void SonicGPIOComponent::set_timeout_us(uint32_t timeout_us) { this->timeout_us_ = timeout_us; }

}  // namespace sonic_gpio
}  // namespace esphome
