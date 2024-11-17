#include "view.h"

std::string format_hour(int hour) {
    if (hour > 9) {
        return std::to_string(hour);
    } else {
        std::string pre = " ";
        std::string num = std::to_string(hour);
        return pre + num;
    }
}

std::string format_minute(int minute) {
    if (minute > 9) {
        return std::to_string(minute);
    } else {
        std::string pre = "0";
        std::string num = std::to_string(minute);
        return pre + num;
    }
}

void AlarmClockView::update(AlarmClockModel &model, Time &machine_time) {
    
    bool flash_display = false;

    if (model.flash_display || model.is_alarm_active()) {
        int secs = machine_time.seconds;
        flash_display = secs % 2 == 0;
    }
    Time lbp = model.last_button_press_time;
    if (flash_display &&
        lbp.difference_with(machine_time).to_total_ms() < 500) {
        flash_display = false;
    }
    if (model.state == AlarmClockStates::ALARM_ACTIVE) {
        flash_display = false;
    }
    if (flash_display && model.has_button_down) {
        flash_display = false;
    }

    Time actual_time = machine_time.offset_with(model.hour_offset, model.minute_offset);
    switch (model.state) {
    case AlarmClockStates::BLANK:
        // Blank mode
        break;
    case AlarmClockStates::DISPLAY_TIME:
    case AlarmClockStates::ALARM_ACTIVE:
        // Display time in "H.MM" format
        if (flash_display) {
            display->clear();
        } else {
            std::string time_str;
            if (!model.flash_display && actual_time.seconds % 2 == 1) {
                time_str = format_hour(actual_time.hour) + format_minute(actual_time.minute);
            } else {
                time_str =
                    format_hour(actual_time.hour) + "." + format_minute(actual_time.minute);
            }
            
            if (model.is_alarm_enabled) {
                time_str += ".";
            }
            display->write(time_str);
        }
        break;
    case AlarmClockStates::SET_TIME_HOUR:
        // Set time hour, flash hour if flash is True
        if (flash_display) {
            display->write("  ." + format_minute(actual_time.minute));
        } else {
            std::string time_str =
                format_hour(actual_time.hour) + "." + format_minute(actual_time.minute);
            display->write(time_str);
        }
        break;
    case AlarmClockStates::SET_TIME_MINUTES:
        // Set time minutes, flash minutes if flash is True
        if (flash_display && !model.has_button_down) {
            display->write(format_hour(actual_time.hour) + ".  ");
        } else {
            std::string time_str =
                format_hour(actual_time.hour) + "." + format_minute(actual_time.minute);
            display->write(time_str);
        }
        break;
    case AlarmClockStates::SET_ALARM_HOUR:
        // Set alarm hour, flash hour if flash is True
        if (flash_display) {
            display->write("  ." + format_minute(model.alarm_minute));
        } else {
            std::string alarm_str = format_hour(model.alarm_hour) + "." +
                                    format_minute(model.alarm_minute);
            display->write(alarm_str);
        }
        break;
    case AlarmClockStates::SET_ALARM_MINUTES:
        // Set alarm minutes, flash minutes if flash is True
        if (flash_display) {
            display->write(format_hour(model.alarm_hour) + ".  ");
        } else {
            std::string prefix = model.alarm_minute < 10 ? "0" : "";
            std::string alarm_str = format_hour(model.alarm_hour) + "." +
                                    format_minute(model.alarm_minute);
            display->write(alarm_str);
        }
        break;
    default:
        break;
    }
}

void AlarmClockView::increase_brightness() {
    float increase_value = display_brightness_direction * 0.01f;
    float new_value = display->get_brightness() + increase_value;
    if (new_value < 0.0f || new_value > 1.0f) {
        display_brightness_direction *= -1;
        new_value = display->get_brightness() - increase_value;
    }
    display->set_brightness(new_value);
}

void AlarmClockView::write(const std::string &text) { display->write(text); }

void AlarmClockView::clear() { display->clear(); }

void AlarmClockView::set_brightness(float brightness) {
    display->set_brightness(brightness);
}

float AlarmClockView::get_brightness() const {
    return display->get_brightness();
}