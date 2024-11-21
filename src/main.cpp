#include <vector>
#include "components/sevsegdisplay.h"
#include "logic/controller.h"
#include "logic/state.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "time/clock.h"
#include "util/logger.h"

// GPIO pins for segments A, B, C, D, E, F, G, Dp
const std::vector<uint> SEGMENT_DISPLAY_GPIO_PINS = {14, 10, 19, 17,
                                                     16, 13, 20, 18};
// GPIO pins for digits in reverse order: 4, 3, 2, 1
const std::vector<uint> SEGMENT_DISPLAY_DIGITSELECT_GPIO_PINS = {15, 12, 11, 21};
Display *display = new SevenSegmentDisplay(SEGMENT_DISPLAY_GPIO_PINS,
                                SEGMENT_DISPLAY_DIGITSELECT_GPIO_PINS, 0.6f);
AlarmClockController *alarmclock = new AlarmClockController(display);

void 
run_display_loop_on_2nd_core() {
   alarmclock->run_update_view_loop();
}

int 
main() {
    stdio_init_all();
    log("Starting alarm clock.");

    SevenSegmentDisplay display(SEGMENT_DISPLAY_GPIO_PINS,
                                SEGMENT_DISPLAY_DIGITSELECT_GPIO_PINS, 0.6f);
    alarmclock = new AlarmClockController(&display);
    Clock::reset_hardware_time();
    multicore_launch_core1(run_display_loop_on_2nd_core);
    alarmclock->run_alarm_clock_loop();
    return 0;
}
