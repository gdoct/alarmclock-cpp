#include "model.h"

AlarmClockModel::AlarmClockModel()
        : state(new AlarmClockState()) {
        state->set_last_button_press_time(0);
        state->set_has_button_down(false);
}

AlarmClockModel::~AlarmClockModel() {
    delete state;
}

int 
AlarmClockModel::increment_mode() {
    state->set_mode(static_cast<AlarmClockModes>((state->get_mode() + 1) %
                                          AlarmClockModes::ALARM_ACTIVE));
    auto mode = state->get_mode();
    if (mode == SET_TIME_HOUR || mode== SET_TIME_MINUTES ||
        mode == SET_ALARM_HOUR || mode == SET_ALARM_MINUTES) {
        state->set_flash_display(true);
    } else if (mode == BLANK || mode == DISPLAY_TIME) {
        state->set_flash_display(false);
    }
    log("state is now %d", mode);
    return mode;
}

bool 
AlarmClockModel::check_alarm() {
    if (!state->get_is_alarm_enabled()) {
        return false;
    }
    if (state->get_mode() == ALARM_ACTIVE) {
        return !state->get_snoozing();
    }
    if (!Clock::is_alarm_triggered(state->get_hour_offset(), state->get_minute_offset(), state->get_alarm_hour(),
                                  state->get_alarm_minute())) {
        return false;
    }
    raise_alarm();
    return true;
}

void 
AlarmClockModel::raise_alarm() {
    log("ALARM!");
    state->set_mode(ALARM_ACTIVE);
    state->set_snoozing(false);
}

// user presses "increase" button to increase some value depending on the state
void 
AlarmClockModel::increase_value() {
    if (state->get_mode() == SET_TIME_HOUR) {
        state->set_hour_offset((state->get_hour_offset() + 1) % 24);
        log("hour offset is now %d", state->get_hour_offset());
    } else if (state->get_mode() == SET_TIME_MINUTES) {
        state->set_minute_offset((state->get_minute_offset() + 1) % 60);
        auto now = Clock::now();
        if (state->get_minute_offset() == 0) {
            state->set_hour_offset(state->get_hour_offset() + 1);
        } else if (state->get_minute_offset() + now.minute == 60) {
            state->set_hour_offset(state->get_hour_offset() - 1);
        }
        log("minute offset is now %d", state->get_minute_offset());
    } else if (state->get_mode() == SET_ALARM_HOUR) {
        state->set_alarm_hour((state->get_alarm_hour() + 1) % 24);
        log("alarm hour is now %d", state->get_alarm_hour());
    } else if (state->get_mode() == SET_ALARM_MINUTES) {
        state->set_alarm_minute((state->get_alarm_minute() + 1) % 60);
        log("alarm minute is now %d", state->get_alarm_minute());
    }
}

AlarmClockState* AlarmClockModel::get_state() const {
    return state;
}