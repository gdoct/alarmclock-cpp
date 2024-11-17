#pragma once
#include "constants.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <cstdint>
#include <iostream>

class RgbLed {
public:
  void toggle(void);
  void on(void);
  void off(void);
  void set_rgb_u16(const uint16_t &r, const uint16_t &g, const uint16_t &b);
  void set_light_u16(const uint16_t &value) { set_rgb_u16(value, value, value); }
  void set_rgb_u8(const uint8_t &r, const uint8_t &g, const uint8_t &b, const uint8_t &intensity);
  void set_light_u8(const uint8_t &value, const uint8_t &intensity) { set_rgb_u8(value, value, value, intensity); }
  bool is_led_on(void);

  RgbLed(const uint &pin_r = LEDLIGHT_R_PIN, 
         const uint &pin_g = LEDLIGHT_G_PIN,
         const uint &pin_b = LEDLIGHT_B_PIN,
         const uint &freq = 500);

private:
  uint pin_r;
  uint pin_g;
  uint pin_b;
  uint slice_num_r;
  uint slice_num_g;
  uint slice_num_b;
  bool light_on;
};
