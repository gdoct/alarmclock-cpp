#include "sevsegdisplay.h"
SevenSegmentDisplay::SevenSegmentDisplay(const std::vector<uint> &segments_pins,
                                         const std::vector<uint> &digits_pins,
                                         float brightness)
    : Display(brightness), segments_pins(segments_pins),
      digits_pins(digits_pins) {
    for (auto pin : segments_pins) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }
    for (auto pin : digits_pins) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }
    clear();
}

std::unordered_map<char, uint8_t> SevenSegmentDisplay::segment_map = {
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

void SevenSegmentDisplay::clear() {
    for (auto pin : segments_pins) {
        gpio_put(pin, 0);
    }
    for (auto pin : digits_pins) {
        disable_digit(pin);
    }
}

void SevenSegmentDisplay::write(const std::string &str) {
    int digit = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];
        if (ch == '.')
            continue;
        bool add_dot = (i + 1 < str.size() && str[i + 1] == '.');
        if (segment_map.find(ch) != segment_map.end()) {
            set_digit(digit, ch, add_dot);
            ++digit;
        }
    }
}

void SevenSegmentDisplay::test_segments() {
    for (size_t i = 0; i < segments_pins.size(); ++i) {
        clear();
        log("Testing segment %zu (pin %u)", i, segments_pins[i]);
        for (size_t c = 0; c < 4; c++) {
            activate_digit(c);
            gpio_put(segments_pins[i], 1);
            sleep_us(30);
        }
        sleep_ms(LED_DISPLAY_WAIT_BETWEEN_CHARACTERS_US); // Light up each segment for 500ms
    }
    clear(); // Clear all segments after testing
}

void SevenSegmentDisplay::enable_digit(uint digit_pin) {
    gpio_put(digit_pin, 0);
}

void SevenSegmentDisplay::disable_digit(uint digit_pin) {
    gpio_put(digit_pin, 1);
}

void SevenSegmentDisplay::activate_digit(uint digit_id) {
    enable_digit(digits_pins[digit_id]);
}

void SevenSegmentDisplay::set_digit(uint digit_id, char value, bool add_dot) {
    clear();
    if (digit_id >= 0 && digit_id < digits_pins.size() &&
        segment_map.find(value) != segment_map.end()) {
        enable_digit(digits_pins[digit_id]);
        uint8_t segments = segment_map[value];
        if (add_dot) {
            segments |= segment_map['.'];
        }
        for (int i = 0; i < 8; ++i) {
            gpio_put(segments_pins[i], (segments >> i) & 0x01);
        }

        // Control brightness by adjusting on-time
        int on_time_us = static_cast<int>(LED_DISPLAY_WAIT_BETWEEN_CHARACTERS_US * brightness);
        sleep_us(on_time_us);

        // Clear the digit after the on-time to adjust perceived brightness
        clear();
        sleep_us(LED_DISPLAY_WAIT_BETWEEN_CHARACTERS_US - on_time_us); // Remaining off-time for this digit
    }
}