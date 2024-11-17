#include "controller.h"
#include <constants.h>

AlarmClockController::AlarmClockController(Display *display)
    : view(display), rgb_led(), led_intensity(0), state() {

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
    increase_light(now);
}

void AlarmClockController::update_view(Time &current_time) {
    state.has_button_down = has_button_down();
    view.update(state, current_time);
    increase_light(current_time);
}

// Interrupt handlers
void AlarmClockController::handle_alarm_button_interrupt() {
    state.last_button_press_time = alarm_btn->last_button_press_time();
    state.is_alarm_enabled = !state.is_alarm_enabled;
}

void AlarmClockController::handle_light_button_interrupt() {
    state.last_button_press_time = light_btn->last_button_press_time();
    if (rgb_led.is_led_on()){
        rgb_led.off();
        if (state.state == AlarmClockStates::ALARM_ACTIVE) {
            state.snoozing = true;
        }
    } else {
        start_minimal_light();
    }
}

void AlarmClockController::handle_mode_button_interrupt() {
    state.last_button_press_time = mode_btn->last_button_press_time();
    int newmode = state.increment_mode();
    printf("mode is now %s\n", AlarmClockStateNames[newmode]);
}

void AlarmClockController::handle_increase_button_interrupt() {
    state.last_button_press_time = increase_btn->last_button_press_time();
    AlarmClockStates clockstate = state.state;
    if (clockstate == AlarmClockStates::DISPLAY_TIME) {
        view.increase_brightness();
    } else {
        state.increase_value();
    }
}

void AlarmClockController::run_alarm_clock_step() {
    Time now = Time::now();
    update_view(now);
    state.check_alarm();
    Button::process_events();
}

void AlarmClockController::run_alarm_clock_loop() {
    while (true) {
        run_alarm_clock_step();
        sleep_us(ALARMCLOCK_LOOP_SLEEP_US);
    }
}

bool AlarmClockController::get_flash_display() { 
    return (state.flash_display); 
}

void AlarmClockController::increase_light(Time &current_time) {
    if (led_intensity == UINT16_T_MAX) return;
    if (!rgb_led.is_led_on()) { 
        return;
    }
    auto starttime = light_btn->last_button_press_time();
    auto diff = current_time.difference_with(starttime);
    if (diff.subseconds % 25 == 0) {
        led_intensity += 1;
        uint8_t actualvalue = led_intensity >> 8;
        rgb_led.set_rgb_u8(actualvalue, actualvalue, actualvalue, actualvalue);
    }
}

void AlarmClockController::start_minimal_light() { 
    led_intensity = 0x100; 
    rgb_led.set_rgb_u8(1, 1, 1, 1);
}
