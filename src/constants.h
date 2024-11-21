#pragma once
#include <cstdint>
using RawTime = uint64_t;

class Constants {
    public:
        static const uint8_t  LED_INTENSITY_MAX = 0xFF;
        static const uint8_t  LED_INTENSITY_MIN = 0x00;
        static const uint16_t MINIMUM_LED_INTENSITY = 0x100; // minimal light
        static const uint16_t UINT16_T_MAX = 0xFFFF;
        static const uint32_t LED_INTENSITY_INCREASE_MS = 1; // 2^16 (65k) steps. * 1 ms = 65 sec
        static const RawTime  BUTTON_CLICK_DEBOUNCE_US = 20000;
        static const RawTime  BUTTON_HOLD_INITIAL_DELAY_US = 300000;
        static const RawTime  BUTTON_HOLD_REPEAT_DELAY_US = 120000;
        static const RawTime  ALARMCLOCK_LOOP_SLEEP_MS = 0;
        static const RawTime  LED_DISPLAY_WAIT_BETWEEN_CHARACTERS_US = 2000;
        static const RawTime  SEGMENT_WAIT_US = 20;

        static const uint32_t TARGET_FREQUENCY_HZ = 200; // Desired frequency in Hz
        static const uint32_t TARGET_CYCLE_TIME_US =
            1000000 / TARGET_FREQUENCY_HZ; // Microseconds per cycle (1000000
                                    // microseconds in a second)

};
