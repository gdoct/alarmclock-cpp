#include "clock.h"

static RawTime BOOT_TIME_OFFSET = 0;

RawTime 
get_hardware_time_u64(void) { 
    // Reading low latches the high value 
    uint32_t lo = timer_hw->timelr; 
    uint32_t hi = timer_hw->timehr; 
    return ((RawTime)hi << 32u) | lo; 
}

void 
Clock::reset_hardware_time(void) {
    BOOT_TIME_OFFSET = get_hardware_time_u64();
}

Time 
Clock::get_hardware_time(void) {
    if (BOOT_TIME_OFFSET == 0) {
        reset_hardware_time();
    }
    RawTime hwtime = get_hardware_time_u64() - BOOT_TIME_OFFSET;
    return Time::from_raw_time(hwtime);
}

// Function to check if the alarm should be triggered
bool 
Clock::is_alarm_triggered(int hour_offset, int minute_offset, int alarm_hour, int alarm_minute) {
    Time now = Clock::now().offset_with(hour_offset, minute_offset);

    if (now.hour != alarm_hour) {
        return false;
    }

    if (now.hour == alarm_hour && now.minute == alarm_minute && now.seconds == 0) {
        return true;
    }

    return false;
}

Time 
Clock::now(void) {
    return get_hardware_time();
}

RawTime 
Clock::get_raw_time( void ){
    return get_hardware_time_u64();
}

