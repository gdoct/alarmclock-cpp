#include "controller.h"
#include "constants.h"

AlarmClockController::AlarmClockController(Display *display)
    : view(display), rgb_led(), led_intensity(0), model(), last_led_increase({ 0, 0, 0, 0 }) {
    // GPIO setup
    alarm_btn = new Button("alarm", SNOOZE_BUTTON_PIN,
                           [this] { handle_alarm_button_interrupt(); });
    mode_btn = new Button("mode", MODE_BUTTON_PIN,
                          [this] { handle_mode_button_interrupt(); });
    increase_btn = new Button(
        "increase", INCREASE_BUTTON_PIN,
        [this] { handle_increase_button_interrupt(); },
        [this] { update_view_idle(); }, true);
    light_btn = new Button("light", LIGHT_BUTTON_PIN,
                           [this] { handle_light_button_interrupt(); });
}

AlarmClockController::~AlarmClockController() {
    delete alarm_btn;
    delete mode_btn;
    delete increase_btn;
    delete light_btn;
}

bool AlarmClockController::has_button_down() {
    return increase_btn->is_held();
}

void AlarmClockController::update_view_idle() {
    Time now = Time::now();
    update_view(now);
}

void AlarmClockController::update_view(Time &current_time) {
    view.update(model.get_state(), current_time);
    increase_light(current_time);
}

// Interrupt handlers
void AlarmClockController::handle_alarm_button_interrupt() {
    std::unique_ptr<AlarmClockState> state = model.get_state();
    state->last_button_press_time = alarm_btn->get_last_button_press_time();
    
    switch (state->mode) {
        case AlarmClockModes::SET_ALARM_HOUR:
        case AlarmClockModes::SET_ALARM_MINUTES: {
            Time now = Time::now();
            state->alarm_hour = now.hour;
            if (now.seconds > 55) 
            {
                state->set_alarm_minute(state->alarm_minute + 1);
            } 
            state->set_alarm_minute(state->alarm_minute + 1);
            break;
        }
        case AlarmClockModes::SET_TIME_HOUR:
        case AlarmClockModes::SET_TIME_MINUTES: {
                state->set_alarm_hour(0);
                state->set_alarm_minute(0);
            break;
        }
        default: {
            model.get_state()->is_alarm_enabled = !model.get_state()->is_alarm_enabled;
            break;
        }
    }
}

void AlarmClockController::handle_light_button_interrupt() {
    std::unique_ptr<AlarmClockState> state = model.get_state();
    state->set_last_button_press_time(light_btn->get_last_button_press_time());
    if (rgb_led.is_led_on()){
        rgb_led.off();
        if (state->mode == AlarmClockModes::ALARM_ACTIVE) {
            state->set_snoozing(true);
        }
    } else {
        start_minimal_light();
    }
}

void AlarmClockController::handle_mode_button_interrupt() {
    std::unique_ptr<AlarmClockState> state = model.get_state();
    state->set_last_button_press_time(mode_btn->get_last_button_press_time());
    int newmode = model.increment_mode();
    log("mode is now %s", AlarmClockStateNames[newmode]);
}

void AlarmClockController::handle_increase_button_interrupt() {
    std::unique_ptr<AlarmClockState> state = model.get_state();
    state->set_last_button_press_time(increase_btn->get_last_button_press_time());
    AlarmClockModes clockstate = state->mode;
    if (clockstate == AlarmClockModes::DISPLAY_TIME) {
        view.increase_brightness();
    } else {
        model.increase_value();
    }
}

void AlarmClockController::run_alarm_clock_step() {
    Time now = Time::now();
    model.get_state()->has_button_down = has_button_down();
    update_view(now);
    if (model.check_alarm()) {
        start_minimal_light();
    }
    Button::process_events();
}

void AlarmClockController::run_alarm_clock_loop() {
    while (true) {
        run_alarm_clock_step();
        sleep_us(ALARMCLOCK_LOOP_SLEEP_US);
    }
}

bool AlarmClockController::get_flash_display() { 
    return (model.get_state()->flash_display); 
}

void AlarmClockController::increase_light(Time &current_time) {
    if (led_intensity == UINT16_T_MAX) return;
    if (!rgb_led.is_led_on()) { 
        return;
    }
    auto diff = current_time.difference_with(last_led_increase);
    if (diff.to_total_ms() > 2) {
        led_intensity += 1;
        uint8_t actualvalue = led_intensity >> 8;
        rgb_led.set_rgb_u8(actualvalue, actualvalue, actualvalue, actualvalue);
        last_led_increase = Time::now();
    }
}

void AlarmClockController::start_minimal_light() { 
    led_intensity = 0x100; 
    rgb_led.set_rgb_u8(1, 1, 1, 1);
    last_led_increase = Time::now();
}
