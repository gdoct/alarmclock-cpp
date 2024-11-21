#include "time.h"

Time
Time::offset_with(const int hours, const int minutes) const {
    Time othertime = { hours, minutes, 0, 0};
    return *this + othertime;
}

Time 
Time::absolute_difference_with(const Time& othertime) const {
    if (Time::operator>(othertime)) {
        return *this - othertime;
    } else {
        return othertime - *this;
    }
}

RawTime 
Time::to_raw_time() const {
    return (static_cast<uint64_t>(hour) * 3600000ULL) + 
           (static_cast<uint64_t>(minute) * 60000ULL) + 
           (static_cast<uint64_t>(seconds) * 1000ULL) + 
           (static_cast<uint64_t>(subseconds) / 1000ULL); 
}


Time 
Time::from_raw_time(RawTime raw_time) {
    uint64_t total_seconds = raw_time / 1000000;
    int subseconds = (raw_time % 1000000) / 1000; 

    int seconds = total_seconds % 60;
    int minutes = (total_seconds / 60) % 60;
    int hours = (total_seconds / 3600) % 24;

    return {hours, minutes, seconds, subseconds};
}

// Operator Overloads
bool 
Time::operator==(const Time &other) const {
    return hour == other.hour &&
           minute == other.minute &&
           seconds == other.seconds &&
           subseconds == other.subseconds;
}

Time 
Time::operator+(const Time &other) const {
    Time result;
    result.subseconds = subseconds + other.subseconds;
    result.seconds = seconds + other.seconds + result.subseconds / 1000;
    result.subseconds %= 1000;
    result.minute = minute + other.minute + result.seconds / 60;
    result.seconds %= 60;
    result.hour = hour + other.hour + result.minute / 60;
    result.minute %= 60;
    result.hour %= 24; 
    return result;
}

Time 
Time::operator-(const Time &other) const {
    Time result;
    int carry = 0;

    result.subseconds = subseconds - other.subseconds;
    if (result.subseconds < 0) {
        result.subseconds += 1000;
        carry = 1;
    }

    result.seconds = seconds - other.seconds - carry;
    carry = 0;
    if (result.seconds < 0) {
        result.seconds += 60;
        carry = 1;
    }

    result.minute = minute - other.minute - carry;
    carry = 0;
    if (result.minute < 0) {
        result.minute += 60;
        carry = 1;
    }

    result.hour = hour - other.hour - carry;
    if (result.hour < 0) {
        result.hour += 24; 
    }

    return result;
}

bool 
Time::operator>(const Time &other) const {
    if (hour > other.hour) return true;
    if (hour < other.hour) return false;
    if (minute > other.minute) return true;
    if (minute < other.minute) return false;
    if (seconds > other.seconds) return true;
    if (seconds < other.seconds) return false;
    return subseconds > other.subseconds;
}

bool 
Time::operator<(const Time &other) const {
    if (hour < other.hour) return true;
    if (hour > other.hour) return false;
    if (minute < other.minute) return true;
    if (minute > other.minute) return false;
    if (seconds < other.seconds) return true;
    if (seconds > other.seconds) return false;
    return subseconds < other.subseconds;
}

