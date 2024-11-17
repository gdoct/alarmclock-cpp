#include "state.h"

AlarmClockState::AlarmClockState() : mode(DISPLAY_TIME), hour_offset(6), minute_offset(59),
    alarm_hour(7), alarm_minute(0), light_on(false), snoozing(false),
    flash_display(true), is_alarm_enabled(true) {}

bool AlarmClockState::is_alarm_active() const {
    return mode == ALARM_ACTIVE && !snoozing;
}

// Accessor methods
AlarmClockModes AlarmClockState::get_mode() const {
    return mode;
}

void AlarmClockState::set_mode(AlarmClockModes mode) {
    this->mode = mode;
}

int AlarmClockState::get_hour_offset() const {
    return hour_offset;
}

void AlarmClockState::set_hour_offset(int hour_offset) {
    this->hour_offset = hour_offset;
}

int AlarmClockState::get_minute_offset() const {
    return minute_offset;
}

void AlarmClockState::set_minute_offset(int minute_offset) {
    this->minute_offset = minute_offset;
}

int AlarmClockState::get_alarm_hour() const {
    return alarm_hour;
}

void AlarmClockState::set_alarm_hour(int alarm_hour) {
    this->alarm_hour = alarm_hour;
}

int AlarmClockState::get_alarm_minute() const {
    return alarm_minute;
}

void AlarmClockState::set_alarm_minute(int alarm_minute) {
    this->alarm_minute = alarm_minute;
}

bool AlarmClockState::get_light_on() const {
    return light_on;
}

void AlarmClockState::set_light_on(bool light_on) {
    this->light_on = light_on;
}

bool AlarmClockState::get_snoozing() const {
    return snoozing;
}

void AlarmClockState::set_snoozing(bool snoozing) {
    this->snoozing = snoozing;
}

bool AlarmClockState::get_flash_display() const {
    return flash_display;
}

void AlarmClockState::set_flash_display(bool flash_display) {
    this->flash_display = flash_display;
}

bool AlarmClockState::get_has_button_down() const {
    return has_button_down;
}

void AlarmClockState::set_has_button_down(bool has_button_down) {
    this->has_button_down = has_button_down;
}

bool AlarmClockState::get_is_alarm_enabled() const {
    return is_alarm_enabled;
}

void AlarmClockState::set_is_alarm_enabled(bool is_alarm_enabled) {
    this->is_alarm_enabled = is_alarm_enabled;
}

Time AlarmClockState::get_last_button_press_time() const {
    return last_button_press_time;
}

void AlarmClockState::set_last_button_press_time(const Time &last_button_press_time) {
    this->last_button_press_time = last_button_press_time;
}
