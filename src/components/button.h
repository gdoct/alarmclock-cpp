#pragma once

#include "pico/stdlib.h"
#include "constants.h"
#include "time/clock.h"
#include "time/scheduler.h"
#include "util/logger.h"
#include "hardware/gpio.h"
#include <chrono>
#include <functional>
#include <unordered_map>
#include <string>
#include <queue>

struct Event {
      uint pin;
      uint32_t events;
      RawTime time;
  };
  
class Button {
  public:
    Button(const std::string &name, const uint &pin,
           const std::function<void()> callback = nullptr,
           const bool &allow_hold = false);

    ~Button();

    bool is_held(void);
    volatile RawTime& get_last_button_press_time(void);
    static bool is_any_button_held(void);
    static bool is_button_held(uint pinid);
    static void process_events(void);

  private:
    static std::unordered_map<uint, Button *> BUTTON_INSTANCES;
    static std::queue<Event> EVENT_QUEUE;
    
    std::string name;
    uint pin;
    std::function<void()> callback;
    bool allow_hold;
    volatile RawTime last_press_time;

    void handle_interrupt(void);
    bool is_debounced(RawTime &now);
    void process_button_hold(RawTime &now);
    
    static void gpio_callback(uint gpio, uint32_t events);
};
