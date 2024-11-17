#pragma once

#include "util/clockfunctions.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

enum AlarmClockModes {
    BLANK = 0,
    DISPLAY_TIME,
    SET_TIME_HOUR,
    SET_TIME_MINUTES,
    SET_ALARM_HOUR,
    SET_ALARM_MINUTES,
    ALARM_ACTIVE
};

struct AlarmClockState {
    AlarmClockModes mode;
    int hour_offset;
    int minute_offset;
    int alarm_hour;
    int alarm_minute;
    bool light_on;
    bool snoozing;
    bool flash_display;
    bool has_button_down;
    bool is_alarm_enabled;
    Time last_button_press_time;

    AlarmClockState();

    bool is_alarm_active() const;

    // Accessor methods
    AlarmClockModes get_mode() const;
    void set_mode(AlarmClockModes mode);

    int get_hour_offset() const;
    void set_hour_offset(int hour_offset);

    int get_minute_offset() const;
    void set_minute_offset(int minute_offset);

    int get_alarm_hour() const;
    void set_alarm_hour(int alarm_hour);

    int get_alarm_minute() const;
    void set_alarm_minute(int alarm_minute);

    bool get_light_on() const;
    void set_light_on(bool light_on);

    bool get_snoozing() const;
    void set_snoozing(bool snoozing);

    bool get_flash_display() const;
    void set_flash_display(bool flash_display);

    bool get_has_button_down() const;
    void set_has_button_down(bool has_button_down);

    bool get_is_alarm_enabled() const;
    void set_is_alarm_enabled(bool is_alarm_enabled);

    Time get_last_button_press_time() const;
    void set_last_button_press_time(const Time &last_button_press_time);
};
