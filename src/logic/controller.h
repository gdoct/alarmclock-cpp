#pragma once

#include <iostream>
#include "pico/stdlib.h"
#include "constants.h"
#include "pinlayout.h"
#include "components/button.h"
#include "components/display.h"
#include "components/rgbled.h"
#include "logic/model.h"
#include "logic/view.h"
#include "time/clock.h"
#include "time/scheduler.h"

class AlarmClockController {
public:

    AlarmClockController(Display *display);
    ~AlarmClockController();

    void run_alarm_clock_step(void);
    void run_alarm_clock_loop(void);
    void run_update_view_loop(void);
    void update_view(Time &current_time);

    void handle_alarm_button_interrupt(void);
    void handle_light_button_interrupt(void);
    void handle_mode_button_interrupt(void);
    void handle_increase_button_interrupt(void);

    AlarmClockState* get_state() const; 

    bool has_button_down(void);
    bool get_flash_display(void);
    void increase_light(Time &current_time);
    void start_minimal_light(void);

private:
    AlarmClockModel model;
    AlarmClockView view;
    Button* alarm_btn;
    Button* mode_btn;
    Button* increase_btn;
    Button* light_btn;
    RgbLed rgb_led;
    uint16_t led_intensity;
    Time last_led_increase;
};
