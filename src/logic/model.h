#pragma once
#ifndef ALARMCLOCKMODEL_H
#define ALARMCLOCKMODEL_H

#include "util/clockfunctions.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

enum AlarmClockStates {
    BLANK = 0,
    DISPLAY_TIME,
    SET_TIME_HOUR,
    SET_TIME_MINUTES,
    SET_ALARM_HOUR,
    SET_ALARM_MINUTES,
    ALARM_ACTIVE
};

const std::vector<std::string> AlarmClockStateNames = {
    "blank",          "display time",     "set hour", "set minute",
    "set alarm hour", "set alarm minute", "alarm"};

class AlarmClockModel {
  public:
    AlarmClockModel()
        : state(DISPLAY_TIME), hour_offset(0), minute_offset(0),
          alarm_hour(0), alarm_minute(1), light_on(false), snoozing(false),
          flash_display(true), is_alarm_enabled(false) {
        last_button_press_time = {1,2,3,4};
        has_button_down = false;
    }

    int increment_mode();
    bool check_alarm();
    void raise_alarm();
    bool is_alarm_active();
    void increase_value();
    AlarmClockStates state;
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
};

#endif // ALARMCLOCKMODEL_H
