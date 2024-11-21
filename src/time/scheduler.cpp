#include "scheduler.h"

void 
Scheduler::run_with_frequency(uint32_t run_duration_us, uint32_t target_cycle_time_us, std::function<void()> callback) {
    uint32_t run_start_time = timer_hw->timelr; // Take the low word of the time
    uint32_t elapsed_total_us = 0;

    while (elapsed_total_us < run_duration_us) {
        uint32_t start_time = timer_hw->timelr; 
        callback();
        uint32_t end_time = timer_hw->timelr; 
        uint32_t elapsed_time_us = end_time - start_time;

        if (elapsed_time_us < target_cycle_time_us) {
            sleep_us(target_cycle_time_us - elapsed_time_us);
        }
        
        uint32_t final_time = timer_hw->timelr;
        elapsed_total_us = final_time - run_start_time; 
    }
}
