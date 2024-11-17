#include "components/sevsegdisplay.h"
#include "logic/controller.h"
#include "pico/stdlib.h"
#include "util/clockfunctions.h"
#include <vector>

// GPIO pins for segments A, B, C, D, E, F, G, Dp
const std::vector<uint> SEGMENT_DISPLAY_GPIO_PINS = {14, 10, 19, 17,
                                                     16, 13, 20, 18};
// GPIO pins for digits in reverse order: 4, 3, 2, 1
const std::vector<uint> SEGMENT_DISPLAY_DIGITSELECT_GPIO_PINS = {15, 12, 11,
                                                                 21};
void stall_startup(AlarmClockController &alarmclock, Display *display) {
    std::vector<std::string> chars = {
        " ", " ", " ", " ", "g", "u", "I", "d", "O",
        " ", "C", "L", "0", "C", "H", " ", " ",
    };
    int counter = 0;
    int idx = 0;
    while (alarmclock.get_flash_display()) {
        counter += 1;
        if (counter % 25 == 0) {
            idx += 1;
        }
        if (idx + 4 > chars.size()) {
            idx = 0;
        }
        std::string out = chars[idx] + chars[idx + 1] + chars[idx + 2] +
                          chars[idx + 3];

        display->write(out);
        Time now = Time::now();
        if (counter % 25 == 0) {
            printf("the time is %d:%d:%d", now.hour, now.minute, now.seconds);
        }
        sleep_ms(20);
    }
    printf("button detected, starting clock.\n");
}

int main() {
    stdio_init_all();
    printf("Starting alarm clock.\n");

    // Initialize the SevenSegmentDisplay
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
    printf("machinata terminatem es\n");
    return 0;
}
