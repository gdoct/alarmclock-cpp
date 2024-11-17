#pragma once
#include <cstdint>

constexpr uint8_t  LED_INTENSITY_MAX = 0xFF;
constexpr uint8_t  LED_INTENSITY_MIN = 0x00;
constexpr uint16_t MINIMUM_LED_INTENSITY = 0x100; // minimal light
constexpr uint16_t UINT16_T_MAX = 0xFFFF;
constexpr uint32_t LED_INTENSITY_INCREASE_MS = 1; // 2^16 (65k) steps. * 1 ms = 65 sec
constexpr uint32_t BUTTON_CLICK_DEBOUNCE_MS = 200;
constexpr uint32_t BUTTON_HOLD_INITIAL_DELAY_MS = 300;
constexpr uint32_t BUTTON_HOLD_REPEAT_DELAY_MS = 180;
constexpr uint64_t ALARMCLOCK_LOOP_SLEEP_US = 100;
constexpr uint64_t LED_DISPLAY_WAIT_BETWEEN_CHARACTERS_US = 2000;
constexpr uint64_t SEGMENT_WAIT_US = 20;

constexpr uint8_t SNOOZE_BUTTON_PIN = 9;
constexpr uint8_t MODE_BUTTON_PIN = 8;
constexpr uint8_t INCREASE_BUTTON_PIN = 27;
constexpr uint8_t LIGHT_BUTTON_PIN = 26;

constexpr uint8_t LEDLIGHT_R_PIN = 7;
constexpr uint8_t LEDLIGHT_G_PIN = 6;
constexpr uint8_t LEDLIGHT_B_PIN = 5;
