#include "model.h"
#include "util/logger.h"

int AlarmClockModel::increment_mode() {
    state = static_cast<AlarmClockStates>((state + 1) %
                                          AlarmClockStates::ALARM_ACTIVE);
    if (state == SET_TIME_HOUR || state == SET_TIME_MINUTES ||
        state == SET_ALARM_HOUR || state == SET_ALARM_MINUTES) {
        flash_display = true;
    } else if (state == BLANK || state == DISPLAY_TIME) {
        flash_display = false;
    }
    log("state is now %d", state);
    return state;
}

bool AlarmClockModel::check_alarm() {
    if (!is_alarm_enabled) {
        return false;
    }
    if (state == ALARM_ACTIVE) {
        return !snoozing;
    }
    if (!Time::is_alarm_triggered(hour_offset, minute_offset, alarm_hour,
                                  alarm_minute)) {
        return false;
    }
    raise_alarm();
    return true;
}

void AlarmClockModel::raise_alarm() {
    log("ALARM!");
    state = ALARM_ACTIVE;
    snoozing = false;
}

bool AlarmClockModel::is_alarm_active() {
    return state == ALARM_ACTIVE && !snoozing;
}

void AlarmClockModel::increase_value() {
    if (state == SET_TIME_HOUR) {
        hour_offset = (hour_offset + 1) % 24;
        log("hour offset is now %d", hour_offset);
    } else if (state == SET_TIME_MINUTES) {
        minute_offset = (minute_offset + 1) % 60;
        log("minute offset is now %d", minute_offset);
    } else if (state == SET_ALARM_HOUR) {
        alarm_hour = (alarm_hour + 1) % 24;
        log("alarm hour is now %d", alarm_hour);
    } else if (state == SET_ALARM_MINUTES) {
        alarm_minute = (alarm_minute + 1) % 60;
        log("alarm minute is now %d", alarm_minute);
    }
}

// int AlarmClockModel::get_hour_offset() { return hour_offset; }
// int AlarmClockModel::get_minute_offset() { return minute_offset; }
// int AlarmClockModel::get_alarm_hour() { return alarm_hour; }
// int AlarmClockModel::get_alarm_minute() { return alarm_minute; }
// bool AlarmClockModel::get_light_on() { return light_on; }
// bool AlarmClockModel::get_snoozing() { return snoozing; }
// bool AlarmClockModel::get_flash_display() { return flash_display; }