#pragma once

#include "display.h"
#include "constants.h"
#include "pico/stdlib.h"
#include "util/logger.h"
#include <unordered_map>
#include <thread>
#include <vector>

class SevenSegmentDisplay : public Display {
  public:
    SevenSegmentDisplay(const std::vector<uint> &segments_pins,
                        const std::vector<uint> &digits_pins, float brightness);

    void clear(void) override;
    void write(const std::string &str) override;
    void test_segments(void);

  private:
    static std::unordered_map<char, uint8_t> segment_map;

    std::vector<uint> segments_pins;
    std::vector<uint> digits_pins;

    void enable_digit(uint digit_pin);
    void disable_digit(uint digit_pin);
    void activate_digit(uint digit_id);
    void set_digit(uint digit_id, char value, bool add_dot);
};
