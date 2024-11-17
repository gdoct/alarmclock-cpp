#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "pico/stdlib.h"
#include "constants.h"
#include "util/clockfunctions.h"
#include "hardware/gpio.h"
#include <chrono>
#include <functional>
#include <unordered_map>
#include <string>
#include <queue>

struct Event {
      uint pin;
      uint32_t events;
      uint64_t time;
  };
  
class Button {
  public:
    Button(const std::string &name, uint pin, std::function<void()> callback,
           std::function<void()> idle_callback = nullptr,
           bool allow_hold = false);

    ~Button();

    bool is_held();
    static bool is_any_button_held();
    Time last_button_press_time() const;
    
    static void process_events(void);

  private:
    static std::unordered_map<uint, Button *> BUTTON_INSTANCES;

    std::string name;
    uint pin;
    std::function<void()> callback;
    std::function<void()> idle_callback;
    bool allow_hold;
    Time last_press_time;

    void handle_interrupt();
    bool is_debounced(Time &now);

    static void gpio_callback(uint gpio, uint32_t events);
};

#endif // BUTTON_H
