#pragma once

#include <cstdio>
#include <cstdarg>
#include <iostream>
#include "time/clock.h"

template<typename... Args>
static void 
log(const char* format, Args... args) {
    auto now = Clock::now();
    printf("[%02d:%02d:%02d.%03d] ", now.hour, now.minute, now.seconds, now.subseconds);
    printf(format, args...);
    printf("\n");
}
