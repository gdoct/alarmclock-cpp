#include "controller.h"

AlarmClockController::AlarmClockController(Display *display)
    : view(display), 
      rgb_led(LEDLIGHT_R_PIN, LEDLIGHT_B_PIN, LEDLIGHT_B_PIN), 
      led_intensity(0), 
      model(), 
      last_led_increase({ 0, 0, 0, 0 }) {
        alarm_btn = new Button("alarm", 
                                SNOOZE_BUTTON_PIN,
                                [this] { handle_alarm_button_interrupt(); });
        mode_btn = new Button("mode", 
                                MODE_BUTTON_PIN,
                                [this] { handle_mode_button_interrupt(); });
        increase_btn = new Button("increase", 
                                    INCREASE_BUTTON_PIN,
                                    [this] { handle_increase_button_interrupt(); },
                                    true);
        light_btn = new Button("light", 
                                LIGHT_BUTTON_PIN,
                                [this] { handle_light_button_interrupt(); });
}

AlarmClockController::~AlarmClockController() {
    delete alarm_btn;
    delete mode_btn;
    delete increase_btn;
    delete light_btn;
}

void 
AlarmClockController::run_alarm_clock_step() {
    Time machine_time = Clock::now();
    AlarmClockState *state = model.get_state();
    state->set_has_button_down(has_button_down());

    if (model.check_alarm()) {
        start_minimal_light();
    }

    // process outstanding irqs on the main thread
    Button::process_events();
}

void 
AlarmClockController::run_alarm_clock_loop() {
    while (true) {
       run_alarm_clock_step();
       sleep_ms(50);
    }
}

void
AlarmClockController::update_view(Time &current_time) {
    view.update(model.get_state(), current_time);
    increase_light(current_time);
}

void 
AlarmClockController::run_update_view_loop() {
    while (true) {
        Time now  = Clock::now();
        update_view(now);
        sleep_us(5000);
    }
}

// Interrupt handlers
void 
AlarmClockController::handle_alarm_button_interrupt() {
    AlarmClockState *state = model.get_state();
    state->set_last_button_press_time(alarm_btn->get_last_button_press_time());
    
    switch (state->get_mode()) {
        case AlarmClockModes::SET_ALARM_HOUR:
        case AlarmClockModes::SET_ALARM_MINUTES: {
            Time now = Clock::now();
            state->set_alarm_hour(now.hour);
            if (now.seconds > 55) 
            {
                state->set_alarm_minute(state->get_alarm_minute() + 1);
            } 
            state->set_alarm_minute(state->get_alarm_minute() + 1);
            break;
        }
        case AlarmClockModes::SET_TIME_HOUR:
        case AlarmClockModes::SET_TIME_MINUTES: {
                state->set_alarm_hour(0);
                state->set_alarm_minute(0);
            break;
        }
        default: {
            state->set_is_alarm_enabled(!state->get_is_alarm_enabled());
            break;
        }
    }
}

void 
AlarmClockController::handle_light_button_interrupt() {
    AlarmClockState *state = model.get_state();
    state->set_last_button_press_time(light_btn->get_last_button_press_time());
    if (rgb_led.is_led_on()){
        rgb_led.off();
        if (state->get_mode() == AlarmClockModes::ALARM_ACTIVE) {
            state->set_snoozing(true);
        }
    } else {
        start_minimal_light();
    }
}

void 
AlarmClockController::handle_mode_button_interrupt() {
    const char* statenames[] = {
        "blank",          
        "display time",     
        "set hour", 
        "set minute",
        "set alarm hour", 
        "set alarm minute", 
        "alarm"
    };
    AlarmClockState *state = model.get_state();
    state->set_last_button_press_time(mode_btn->get_last_button_press_time());
    int newmode = model.increment_mode();
    log("mode is now %s", statenames[newmode]);
}

void 
AlarmClockController::handle_increase_button_interrupt() {
    AlarmClockState *state = model.get_state();
    state->set_last_button_press_time(increase_btn->get_last_button_press_time());
    AlarmClockModes clockstate = state->get_mode();
    if (clockstate == AlarmClockModes::DISPLAY_TIME) {
        view.increase_brightness();
    } else {
        model.increase_value();
    }
}

AlarmClockState* 
AlarmClockController::get_state() const {
    return model.get_state();
}

bool 
AlarmClockController::has_button_down() {
    return increase_btn->is_held();
}

bool 
AlarmClockController::get_flash_display() { 
    AlarmClockState *state = model.get_state();
    return (state->get_flash_display()); 
}

void 
AlarmClockController::increase_light(Time &current_time) {
    if (led_intensity == Constants::UINT16_T_MAX) return;
    if (!rgb_led.is_led_on()) { 
        return;
    }
    auto diff = current_time.absolute_difference_with(last_led_increase);
    if (diff.to_raw_time() > 2) {
        led_intensity += 1;
        uint8_t actualvalue = led_intensity >> 8;
        rgb_led.set_rgb_u8(actualvalue, actualvalue, actualvalue, actualvalue);
        last_led_increase = Clock::now();
    }
}

void 
AlarmClockController::start_minimal_light() { 
    led_intensity = 0x100; 
    rgb_led.set_rgb_u8(1, 1, 1, 1);
    last_led_increase = Clock::now();
}
