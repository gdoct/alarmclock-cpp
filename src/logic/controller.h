#pragma once
#ifndef ALARMCLOCKCONTROLLER_H
#define ALARMCLOCKCONTROLLER_H

#include <iostream>
#include "pico/stdlib.h"
#include "constants.h"
#include "components/button.h"
#include "components/display.h"
#include "components/rgbled.h"
#include "logic/model.h"
#include "logic/view.h"
#include "util/clockfunctions.h"


class AlarmClockController {
public:

    AlarmClockController(Display* display);
    ~AlarmClockController();

    bool has_button_down(void);
    void update_view_idle(void);
    void update_view(Time &current_time);
    void handle_alarm_button_interrupt(void);
    void handle_light_button_interrupt(void);
    void handle_mode_button_interrupt(void);
    void handle_increase_button_interrupt(void);
    void run_alarm_clock_step(void);
    void run_alarm_clock_loop(void);
    bool get_flash_display(void);
    void increase_light(Time &current_time);
    void start_minimal_light(void);
private:
    AlarmClockView view;
    RgbLed rgb_led;
    uint16_t led_intensity;
    AlarmClockModel model;
    Button* alarm_btn;
    Button* mode_btn;
    Button* increase_btn;
    Button* light_btn;
    Time last_led_increase;
};

#endif // ALARMCLOCKCONTROLLER_H
