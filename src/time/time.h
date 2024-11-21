#pragma once
#include <cstdint>
using RawTime = uint64_t;

struct Time {
    int hour;
    int minute;
    int seconds;
    int subseconds;
    Time absolute_difference_with(const Time& t2) const;
    Time offset_with(const int hours, const int minutes) const;
    RawTime to_raw_time(void) const;
    static Time from_raw_time(RawTime raw_time);

    Time operator+(const Time &other) const; 
    Time operator-(const Time &other) const; 
    bool operator==(const Time &other) const; 
    bool operator>(const Time &other) const; 
    bool operator<(const Time &other) const;
};
