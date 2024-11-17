#pragma once
#ifndef CLOCKFUNCTIONS_H
#define CLOCKFUNCTIONS_H

#include <stdio.h>
#include "pico/stdlib.h"

class Time {
    public:
        int hour;
        int minute;
        int seconds;
        int subseconds;
        Time difference_with(const Time& t2);
        Time offset_with(const int hours, const int minutes);
        uint64_t to_total_ms(void);
        static Time now(void);
        static void reset_hardware_time(void);
        static bool is_alarm_triggered(int &hour_offset, int &minute_offset, int &alarm_hour, int &alarm_minute);
        static uint64_t get_raw_time();
        static Time from_raw_time(uint64_t raw_time);
    private:
        static Time get_hardware_time(void);
};


#endif