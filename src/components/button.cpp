#include "button.h"

static std::queue<Event> event_queue;
std::unordered_map<uint, Button *> Button::BUTTON_INSTANCES;

Button::Button(const std::string &name, const uint &pin,
               const std::function<void()> callback,
               const std::function<void()> idle_callback, const bool &allow_hold)
    : name(name), pin(pin), callback(callback), idle_callback(idle_callback),
      allow_hold(allow_hold) {
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

void Button::gpio_callback(uint gpio, uint32_t events) {
    // Find the button associated with this gpio and call the callback
    uint64_t now = Time::get_raw_time();
    Event ev = {pin : gpio, events : events, time : now};
    event_queue.push(ev);
}

void Button::process_events(void) {
    size_t eventcount = event_queue.size();
    while (!event_queue.empty()) {
        Event event = event_queue.front();
        event_queue.pop();
        if (BUTTON_INSTANCES.find(event.pin) != BUTTON_INSTANCES.end()) {
            auto button = BUTTON_INSTANCES[event.pin];
            button->handle_interrupt();
        } else {
            log("ERROR could not find button instance for pin %s", event.pin);
        }
    }
}

bool Button::is_held() { return (gpio_get(pin) == 0); }

Time Button::get_last_button_press_time() { return last_press_time; }

bool Button::is_debounced(Time &now) {
    auto diff = now.difference_with(last_press_time);
    if (diff.to_total_ms() > BUTTON_CLICK_DEBOUNCE_MS) { 
        last_press_time = now;
        return true;
    }
    return false;
}

void Button::handle_interrupt() {
    Time now = Time::now();
    // last button press should be some ms ago to prevent a bouncing
    // signal triggering this function repeatedly
    if (!is_debounced(now)) {
        return;
    }

    callback();

    if (allow_hold) {
        uint64_t hold_start_ms = now.to_total_ms();
        Time last_handled = Time::now();
        while (gpio_get(pin) == 0) {
            Time current_time = Time::now();
            uint64_t elapsed_ms = current_time.to_total_ms() - hold_start_ms;
            if (elapsed_ms > BUTTON_HOLD_INITIAL_DELAY_MS) { // 300 ms hold delay before auto-trigger
                uint64_t last_handled_duration = current_time.difference_with(last_handled).to_total_ms();
                if (last_handled_duration > BUTTON_HOLD_REPEAT_DELAY_MS) {
                    callback();
                    last_handled = current_time;
                }
            }
            if (idle_callback) {
                idle_callback();
            }
            sleep_us(ALARMCLOCK_LOOP_SLEEP_US);
        }
    }
    last_press_time = Time::now();
}

bool Button::is_any_button_held(){
    for(auto &[key, button]: BUTTON_INSTANCES) {
        if (button->is_held()) { 
            return true;
        }
    }
    return false;
}