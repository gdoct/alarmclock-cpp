#pragma once

#include <functional>
#include <cstdint>
#include "pico/stdlib.h"

class Scheduler {
    public:
        static void run_with_frequency(uint32_t run_duration_us, uint32_t target_cycle_time_us, std::function<void()> callback);
};