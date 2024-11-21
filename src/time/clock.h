#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "constants.h"
#include "time.h"
#include <functional>

using RawTime = uint64_t;

class Clock {
    public:
        static Time now(void);
        static void reset_hardware_time(void);
        static bool is_alarm_triggered(int hour_offset, int minute_offset, int alarm_hour, int alarm_minute);
        static RawTime get_raw_time(void);

      private:
        static Time get_hardware_time(void);
};
