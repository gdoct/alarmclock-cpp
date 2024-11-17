#include "clockfunctions.h"

static uint64_t BOOT_TIME_OFFSET = 0;
// this function is private
uint64_t 
get_hardware_time_u64(void) { 
    // Reading low latches the high value 
    uint32_t lo = timer_hw->timelr; 
    uint32_t hi = timer_hw->timehr; 
    return ((uint64_t)hi << 32u) | lo; 
}

void 
Time::reset_hardware_time(void) {
    printf("init: resetting time\n");
    BOOT_TIME_OFFSET = get_hardware_time_u64();
}

Time 
Time::get_hardware_time(void) {
    if (BOOT_TIME_OFFSET == 0) {
        reset_hardware_time();
    }
    uint64_t hwtime = get_hardware_time_u64() - BOOT_TIME_OFFSET;
    return Time::from_raw_time(hwtime);
}

Time
Time::offset_with(const int hours, const int minutes) {
    int hour_with_offset = (hour + hours) % 24;
    int minute_with_offset = (minute + minutes) % 60;

    // Adjust the hour if minute offset causes an overflow
    if ((minute + minutes) >= 60) {
        hour_with_offset = (hour_with_offset + 1) % 24;
    }
    return {hour_with_offset, minute_with_offset, seconds, subseconds};
}

Time 
Time::difference_with(const Time& t2) {
    int t1_total_seconds = hour * 3600 + minute * 60 + seconds;
    int t2_total_seconds = t2.hour * 3600 + t2.minute * 60 + t2.seconds;

    int t1_total_milliseconds = t1_total_seconds * 1000 + subseconds;
    int t2_total_milliseconds = t2_total_seconds * 1000 + t2.subseconds;

    int diff_milliseconds = t1_total_milliseconds - t2_total_milliseconds;
    if (diff_milliseconds < 0) {
        diff_milliseconds += 24 * 3600 * 1000;  // handle negative differences
    }

    int diff_seconds = (diff_milliseconds / 1000) % 60;
    int diff_minutes = (diff_milliseconds / (1000 * 60)) % 60;
    int diff_hours = (diff_milliseconds / (1000 * 3600)) % 24;
    int diff_subseconds = diff_milliseconds % 1000;

    return {diff_hours, diff_minutes, diff_seconds, diff_subseconds};
}

uint64_t 
Time::to_total_ms(void) {
    uint64_t total_milliseconds = 0;
    total_milliseconds += static_cast<uint64_t>(hour) * 3600 * 1000;
    total_milliseconds += static_cast<uint64_t>(minute) * 60 * 1000;
    total_milliseconds += static_cast<uint64_t>(seconds) * 1000;
    total_milliseconds += static_cast<uint64_t>(subseconds);

    return total_milliseconds;
}

// Function to check if the alarm should be triggered
bool 
Time::is_alarm_triggered(int &hour_offset, int &minute_offset, int &alarm_hour, int &alarm_minute) {
    Time now = Time::now().offset_with(hour_offset, minute_offset);

    if (now.hour != alarm_hour) {
        return false;
    }

    if (now.hour == alarm_hour && now.minute == alarm_minute && now.seconds == 0) {
        return true;
    }

    return false;
}

Time 
Time::now(void) {
    return get_hardware_time();
}

uint64_t Time::get_raw_time(){
    return get_hardware_time_u64();
}

Time Time::from_raw_time(uint64_t raw_time){
    uint64_t total_seconds = raw_time / 1000000;
    int subseconds = (raw_time % 1000000) / 1000; // Convert microseconds to milliseconds

    int seconds = total_seconds % 60;
    int minutes = (total_seconds / 60) % 60;
    int hours = (total_seconds / 3600) % 24;

    return {hours, minutes, seconds, subseconds};
}
