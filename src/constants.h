#pragma once
#include <cstdint>
constexpr int ALARMCLOCK_LOOP_SLEEP_US = 100;
constexpr uint16_t MINIMUM_LED_INTENSITY = 0x100; // minimal light
constexpr uint16_t UINT16_T_MAX = 0xFFFF;
constexpr uint8_t LED_INTENSITY_MAX = 0xFF;
constexpr uint8_t LED_INTENSITY_MIN = 0x00;
constexpr int SEGMENT_WAIT_US = 20;
constexpr int BUTTON_CLICK_DEBOUNCE_MS = 200;
constexpr int BUTTON_HOLD_INITIAL_DELAY_MS = 200;
constexpr int BUTTON_HOLD_REPEAT_DELAY_MS = 200;
constexpr int LED_DISPLAY_WAIT_BETWEEN_CHARACTERS_US = 2000;