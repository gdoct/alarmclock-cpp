#include "model.h"

AlarmClockModel::AlarmClockModel()
        : state(AlarmClockState()) {
        state.last_button_press_time = {1,2,3,4};
        state.has_button_down = false;
    }

int AlarmClockModel::increment_mode() {
    state.mode = static_cast<AlarmClockModes>((state.mode + 1) %
                                          AlarmClockModes::ALARM_ACTIVE);
    if (state.mode == SET_TIME_HOUR || state.mode == SET_TIME_MINUTES ||
        state.mode == SET_ALARM_HOUR || state.mode == SET_ALARM_MINUTES) {
        state.flash_display = true;
    } else if (state.mode == BLANK || state.mode == DISPLAY_TIME) {
        state.flash_display = false;
    }
    log("state is now %d", state.mode);
    return state.mode;
}

bool AlarmClockModel::check_alarm() {
    if (!state.is_alarm_enabled) {
        return false;
    }
    if (state.mode == ALARM_ACTIVE) {
        return !state.snoozing;
    }
    if (!Time::is_alarm_triggered(state.hour_offset, state.minute_offset, state.alarm_hour,
                                  state.alarm_minute)) {
        return false;
    }
    raise_alarm();
    return true;
}

void AlarmClockModel::raise_alarm() {
    log("ALARM!");
    state.mode = ALARM_ACTIVE;
    state.snoozing = false;
}

void AlarmClockModel::increase_value() {
    if (state.mode == SET_TIME_HOUR) {
        state.hour_offset = (state.hour_offset + 1) % 24;
        log("hour offset is now %d", state.hour_offset);
    } else if (state.mode == SET_TIME_MINUTES) {
        state.minute_offset = (state.minute_offset + 1) % 60;
        log("minute offset is now %d", state.minute_offset);
    } else if (state.mode == SET_ALARM_HOUR) {
        state.alarm_hour = (state.alarm_hour + 1) % 24;
        log("alarm hour is now %d", state.alarm_hour);
    } else if (state.mode == SET_ALARM_MINUTES) {
        state.alarm_minute = (state.alarm_minute + 1) % 60;
        log("alarm minute is now %d", state.alarm_minute);
    }
}
std::unique_ptr<AlarmClockState> AlarmClockModel::get_state() {
   return std::make_unique<AlarmClockState>(state);
}