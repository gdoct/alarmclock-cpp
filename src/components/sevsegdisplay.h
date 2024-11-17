#pragma once
#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include "display.h"
#include "constants.h"
#include "pico/stdlib.h"
#include <unordered_map>
#include <thread>
#include <vector>

class SevenSegmentDisplay : public Display {
  public:
    SevenSegmentDisplay(const std::vector<uint> &segments_pins,
                        const std::vector<uint> &digits_pins, float brightness);

    void clear() override;
    void write(const std::string &str) override;
    void test_segments();

  private:
    std::unordered_map<char, uint8_t> segment_map = {
    {' ', 0b00000000}, {'0', 0b00111111}, {'1', 0b00000110}, {'2', 0b01011011},
    {'3', 0b01001111}, {'4', 0b01100110}, {'5', 0b01101101}, {'6', 0b01111101},
    {'7', 0b00000111}, {'8', 0b01111111}, {'9', 0b01101111}, {'.', 0b10000000},
    {'A', 0b01110111}, {'b', 0b01111100}, {'C', 0b00111001}, {'d', 0b01011110},
    {'E', 0b01111001}, {'F', 0b01110001}, {'g', 0b01101111}, {'H', 0b01110110},
    {'I', 0b00110000}, {'j', 0b00001110}, {'L', 0b00111000}, {'n', 0b01010100},
    {'o', 0b01011100}, {'p', 0b01110011}, {'Q', 0b01101011}, {'r', 0b01010000},
    {'S', 0b01101101}, {'t', 0b01111000}, {'u', 0b00111110}, {'y', 0b01101110},
    {'Z', 0b01011011}
};


    std::vector<uint> segments_pins;
    std::vector<uint> digits_pins;

    void enable_digit(uint digit_pin);
    void disable_digit(uint digit_pin);
    void activate_digit(int digit_id);
    void set_digit(int digit_id, char value, bool add_dot);

};

#endif // SEVENSEGMENTDISPLAY_H
