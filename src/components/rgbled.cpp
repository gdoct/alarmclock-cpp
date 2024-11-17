#include "rgbled.h"

RgbLed::RgbLed(uint pin_r, uint pin_g, uint pin_b, uint freq)
    : pin_r(pin_r), pin_g(pin_g), pin_b(pin_b), light_on(false) {
    gpio_set_function(pin_r, GPIO_FUNC_PWM);
    gpio_set_function(pin_g, GPIO_FUNC_PWM);
    gpio_set_function(pin_b, GPIO_FUNC_PWM);

    slice_num_r = pwm_gpio_to_slice_num(pin_r);
    slice_num_g = pwm_gpio_to_slice_num(pin_g);
    slice_num_b = pwm_gpio_to_slice_num(pin_b);

    pwm_set_wrap(slice_num_r, 255);
    pwm_set_wrap(slice_num_g, 255);
    pwm_set_wrap(slice_num_b, 255);

    pwm_set_clkdiv(slice_num_r, 125.0f);
    pwm_set_clkdiv(slice_num_g, 125.0f);
    pwm_set_clkdiv(slice_num_b, 125.0f);

    pwm_set_enabled(slice_num_r, true);
    pwm_set_enabled(slice_num_g, true);
    pwm_set_enabled(slice_num_b, true);

    set_light_u16(0);
}

void RgbLed::toggle() {
    if (light_on) {
        off();
    } else {
        on();
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

bool RgbLed::is_led_on() { return light_on; }