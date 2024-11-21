#include "view.h"
#include "components/button.h"
#include "pinlayout.h"

std::string 
format_hour(int hour) {
    if (hour > 9) {
        return std::to_string(hour);
    } else {
        std::string pre = " ";
        std::string num = std::to_string(hour);
        return pre + num;
    }
}

std::string 
format_minute(int minute) {
    if (minute > 9) {
        return std::to_string(minute);
    } else {
        std::string pre = "0";
        std::string num = std::to_string(minute);
        return pre + num;
    }
}

void 
AlarmClockView::clear() { display->clear(); }

void 
AlarmClockView::write(const std::string &text) { display->write(text); }

void 
AlarmClockView::update(AlarmClockState* state,
                            Time &machine_time) {
    bool flash_display = false;

    if (state->get_flash_display() || state->is_alarm_active()) {
        int secs = machine_time.seconds;
        flash_display = secs % 2 == 0;
    }
    RawTime last_press_time = state->get_last_button_press_time();
    RawTime raw_time = Clock::get_raw_time();
    bool is_held = Button::is_button_held(INCREASE_BUTTON_PIN);
    if (flash_display && is_held) {
        flash_display = false;
    }
    if (state->get_mode() == AlarmClockModes::ALARM_ACTIVE) {
        flash_display = false;
    }
    if (flash_display && state->get_has_button_down()) {
        flash_display = false;
    }
    Time actual_time =
        machine_time.offset_with(state->get_hour_offset(), state->get_minute_offset());
    switch (state->get_mode()) {
        case AlarmClockModes::BLANK:
            // Blank mode
            break;
        case AlarmClockModes::DISPLAY_TIME:
        case AlarmClockModes::ALARM_ACTIVE: {
            if (flash_display) {
                display->clear();
            } else {
                std::string time_str;
                if (!state->get_flash_display() && actual_time.seconds % 2 == 1) {
                    time_str =
                        format_hour(actual_time.hour) + format_minute(actual_time.minute);
                } else {
                    time_str = format_hour(actual_time.hour) + "." +
                            format_minute(actual_time.minute);
                }

                if (state->get_is_alarm_enabled()) {
                    time_str += ".";
                }
                display->write(time_str);
            }
            break;
        }
        case AlarmClockModes::SET_TIME_HOUR: {
            if (flash_display) {
                display->write("  ." + format_minute(actual_time.minute));
            } else {
                std::string time_str = format_hour(actual_time.hour) + "." +
                                    format_minute(actual_time.minute);
                display->write(time_str);
            }
            break;
        }
        case AlarmClockModes::SET_TIME_MINUTES: {

            if (flash_display && !state->get_has_button_down()) {
                display->write(format_hour(actual_time.hour) + ".  ");
            } else {
                std::string time_str = format_hour(actual_time.hour) + "." +
                                    format_minute(actual_time.minute);
                display->write(time_str);
            }
            break;
        }
        case AlarmClockModes::SET_ALARM_HOUR: {
            // Set alarm hour, flash hour if flash is True
            if (flash_display) {
                display->write("  ." + format_minute(state->get_alarm_minute()));
            } else {
                std::string alarm_str = format_hour(state->get_alarm_hour()) + "." +
                                        format_minute(state->get_alarm_minute());
                display->write(alarm_str);
            }
            break;
        }
        case AlarmClockModes::SET_ALARM_MINUTES: {
            // Set alarm minutes, flash minutes if flash is True
            if (flash_display) {
                display->write(format_hour(state->get_alarm_hour()) + ".  ");
            } else {
                std::string prefix = state->get_alarm_minute() < 10 ? "0" : "";
                std::string alarm_str = format_hour(state->get_alarm_hour()) + "." +
                                        format_minute(state->get_alarm_minute());
                display->write(alarm_str);
            }
            break;
        }
        default: {
            break;
        }
    }
}

void 
AlarmClockView::increase_brightness() {
    float increase_value = display_brightness_direction * 0.1f;
    float new_value = display->get_brightness() + increase_value;
    if (new_value < 0.0f || new_value > 1.0f) {
        display_brightness_direction *= -1;
        new_value = display->get_brightness() - increase_value;
    }
    display->set_brightness(new_value);
}

void 
AlarmClockView::set_brightness(const float &brightness) {
    display->set_brightness(brightness);
}

float 
AlarmClockView::get_brightness() const {
    return display->get_brightness();
}