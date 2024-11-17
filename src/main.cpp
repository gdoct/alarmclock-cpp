#include "components/sevsegdisplay.h"
#include "logic/controller.h"
#include "pico/stdlib.h"
#include "util/clockfunctions.h"
#include <vector>
#include "util/logger.h"

// GPIO pins for segments A, B, C, D, E, F, G, Dp
const std::vector<uint> SEGMENT_DISPLAY_GPIO_PINS = {14, 10, 19, 17,
                                                     16, 13, 20, 18};
// GPIO pins for digits in reverse order: 4, 3, 2, 1
const std::vector<uint> SEGMENT_DISPLAY_DIGITSELECT_GPIO_PINS = {15, 12, 11, 21};

int main() {
    stdio_init_all();
    log("Starting alarm clock.");

    SevenSegmentDisplay display(SEGMENT_DISPLAY_GPIO_PINS,
                                SEGMENT_DISPLAY_DIGITSELECT_GPIO_PINS, 0.6f);
    AlarmClockController alarmclock(&display);
    Time::reset_hardware_time();
    try {
        alarmclock.run_alarm_clock_loop();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }
    log("machinata terminatem es");
    return 0;
}
