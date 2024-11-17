#include "rgbled.h"

void RgbLed::toggle() {
  light_on = !light_on;
  if (light_on) {
    on();
  } else {
    off();
  }
}

void RgbLed::on() {
  set_light_u8(1, 1);
  light_on = true;
}

void RgbLed::off() {
  set_light_u8(0, 0);
  light_on = false;
}

void RgbLed::set_rgb_u16(uint16_t r, uint16_t g, uint16_t b) {
  pwm_set_gpio_level(pin_r, r);
  pwm_set_gpio_level(pin_g, g);
  pwm_set_gpio_level(pin_b, b);
  light_on = r > 0 || g > 0 || b > 0;
}

void RgbLed::set_rgb_u8(uint8_t r, uint8_t g, uint8_t b, uint8_t intensity) {
  float u8_max_f = static_cast<float>(LED_INTENSITY_MAX);
  float factor = (UINT16_MAX / u8_max_f) * (intensity / u8_max_f);
  uint16_t scaled_r = static_cast<uint16_t>(r * factor);
  uint16_t scaled_g = static_cast<uint16_t>(g * factor);
  uint16_t scaled_b = static_cast<uint16_t>(b * factor);

  pwm_set_gpio_level(pin_r, scaled_r);
  pwm_set_gpio_level(pin_g, scaled_g);
  pwm_set_gpio_level(pin_b, scaled_b);

  light_on = (r > 0 || g > 0 || b > 0) && intensity > 0;
}

bool RgbLed::is_led_on() {
    return light_on;
}