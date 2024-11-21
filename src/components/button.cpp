#include "button.h"

std::queue<Event> 
Button::EVENT_QUEUE;

std::unordered_map<uint, Button *> 
Button::BUTTON_INSTANCES;

Button::Button(const std::string &name, const uint &pin,
               const std::function<void()> callback, const bool &allow_hold)
    : name(name), pin(pin), callback(callback), allow_hold(allow_hold) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, true,
                                       &Button::gpio_callback);
    BUTTON_INSTANCES[pin] = this;
}

Button::~Button() {
    gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_FALL, false);
    BUTTON_INSTANCES.erase(pin);
}

void 
Button::gpio_callback(uint gpio, uint32_t events) {
    // Find the button associated with this gpio and call the callback
    RawTime now = Clock::get_raw_time();
    Event ev = {pin : gpio, events : events, time : now};

    EVENT_QUEUE.push(ev);
}

void 
Button::process_events(void) {
    while (!EVENT_QUEUE.empty()) {
        Event event = EVENT_QUEUE.front();
        EVENT_QUEUE.pop();
        if (BUTTON_INSTANCES.find(event.pin) != BUTTON_INSTANCES.end()) {
            auto button = BUTTON_INSTANCES[event.pin];
            button->handle_interrupt();
        } else {
            log("ERROR could not find button instance for pin %s", event.pin);
        }
    }
}

bool 
Button::is_held() { return (gpio_get(pin) == 0); }

volatile RawTime& 
Button::get_last_button_press_time() {
    return last_press_time;
} // Time::from_raw_time(last_press_time); }

bool 
Button::is_debounced(RawTime &now) {
    auto diff = now - last_press_time;

    if (diff > Constants::BUTTON_CLICK_DEBOUNCE_US) {
        last_press_time = now;
        return true;
    }
    return false;
}

void 
Button::process_button_hold(RawTime &now) {
    RawTime last_handled = Clock::get_raw_time();
    while (gpio_get(pin) == 0) {
        last_press_time = Clock::get_raw_time();
        RawTime elapsed_since_hold = last_press_time - now;
        if (elapsed_since_hold > Constants::BUTTON_HOLD_INITIAL_DELAY_US) {
            RawTime last_handled_duration = last_press_time - last_handled;

            if (last_handled_duration >
                Constants::BUTTON_HOLD_REPEAT_DELAY_US) {
                callback();
                last_handled = last_press_time;
            }
        }
        RawTime loop_end_time = Clock::get_raw_time();
        RawTime loop_elapsed_time_us = loop_end_time - last_press_time;

        log("Button::process_button_hold->elapsed @ %llu", elapsed_since_hold);
        if (loop_elapsed_time_us < Constants::TARGET_CYCLE_TIME_US) {
            log("Button::process_button_hold->zzz");
            sleep_us(Constants::TARGET_CYCLE_TIME_US - loop_elapsed_time_us);
        } else {
            log("Button::process_button_hold->not fast enough");
        }
    }
    last_press_time = Clock::get_raw_time();
}

void 
Button::handle_interrupt() {
    RawTime now = Clock::get_raw_time();
    // last button press should be some ms ago to prevent a bouncing
    // signal triggering this function repeatedly
    if (!is_debounced(now)) {
        log(" exit button %s is bouncing.", name.c_str());
        return;
    }
    log("button press: %s", name.c_str());
    callback();

    if (allow_hold) {
        process_button_hold(now);
    }
}
bool 
Button::is_any_button_held() {
    for (auto &[key, button] : BUTTON_INSTANCES) {
        if (button->is_held()) {
            return true;
        }
    }
    return false;
}

bool 
Button::is_button_held(uint pinid) {
    for (auto &[key, button] : BUTTON_INSTANCES) {
        if (key == pinid && button->is_held()) {
            return true;
        }
    }
    return false;
}