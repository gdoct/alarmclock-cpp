#pragma once
#ifndef ALARMCLOCKCONTROLLER_H
#define ALARMCLOCKCONTROLLER_H

#include <iostream>
#include "pico/stdlib.h"
#include "components/button.h"
#include "components/display.h"
#include "components/rgbled.h"
#include "logic/model.h"
#include "logic/view.h"
#include "util/clockfunctions.h"


class AlarmClockController {
public:
    static const uint SNOOZE_BUTTON_PIN = 9;
    static const uint MODE_BUTTON_PIN = 8;
    static const uint INCREASE_BUTTON_PIN = 27;
    static const uint LIGHT_BUTTON_PIN = 26;

    AlarmClockController(Display* display);
    ~AlarmClockController();

    bool has_button_down();
    void update_view_idle();
    void update_view(Time &current_time);
    void handle_alarm_button_interrupt();
    void handle_light_button_interrupt();
    void handle_mode_button_interrupt();
    void handle_increase_button_interrupt();
    void run_alarm_clock_step();
    void run_alarm_clock_loop();
    bool get_flash_display();
    void increase_light(Time &current_time);
    void start_minimal_light();
private:
    AlarmClockView view;
    RgbLed rgb_led;
    uint16_t led_intensity;
    AlarmClockModel state;
    Button* alarm_btn;
    Button* mode_btn;
    Button* increase_btn;
    Button* light_btn;
};

#endif // ALARMCLOCKCONTROLLER_H
