#pragma once
#include "constants.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <cstdint>
#include <iostream>

class RgbLed {
public:
  static const uint LEDLIGHT_R_PIN = 7;
  static const uint LEDLIGHT_G_PIN = 6;
  static const uint LEDLIGHT_B_PIN = 5;

  void toggle();
  void on();
  void off();
  void set_rgb_u16(uint16_t r, uint16_t g, uint16_t b);
  void set_light_u16(uint16_t value) { set_rgb_u16(value, value, value); }
  void set_rgb_u8(uint8_t r, uint8_t g, uint8_t b, uint8_t intensity);
  void set_light_u8(uint8_t value, uint8_t intensity) { set_rgb_u8(value, value, value, intensity); }
  bool is_led_on();

  RgbLed(uint pin_r = LEDLIGHT_R_PIN, 
         uint pin_g = LEDLIGHT_G_PIN,
         uint pin_b = LEDLIGHT_B_PIN,
         uint freq = 500);

private:
  uint pin_r;
  uint pin_g;
  uint pin_b;
  uint slice_num_r;
  uint slice_num_g;
  uint slice_num_b;
  bool light_on;
};
