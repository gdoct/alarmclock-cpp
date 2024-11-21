# Raspberry Pi Pico Wakeup light Project

This project demonstrates how to use a 5461AS-1 4-digit 7-segment display with a Raspberry Pi Pico, including 
button control and a LED indicator, to build a retro alarmclock with wake-up light.

## Components and Pins

### Raspberry Pi Pico GPIO Connections

#### 7-Segment Display Connections
**Top Pins (from left to right):**
- GPIO13 - Segment 1
- GPIO2 - Segment 2
- GPIO7 - Segment 3
- GPIO12 - Segment 4
- GPIO11 - Segment 5
- GPIO3 - Segment 6

**Bottom Pins (from left to right):**
- GPIO6 - Segment 7
- GPIO5 - Segment 8
- GPIO9 - Segment 9
- GPIO4 - Segment 10
- GPIO8 - Segment 11
- GPIO10 - Segment 12

#### Control Buttons
- **SNOOZE_PIN**: GPIO 14
- **MODE_PIN**: GPIO 15
- **INCREASE_PIN**: GPIO 16
- **LIGHT_PIN**: GPIO 17

#### LED Light
- **LED**: GPIO 18 (with a 120 ohm current-limiting resistor)

## Breadboard Layout

### Steps to Create the Breadboard Layout:
1. **Place the Raspberry Pi Pico 2 on the Breadboard**: Ensure it's firmly seated with access to its GPIO pins.
2. **Connect the 7-Segment Display**:
   - **Top Pins (from left to right)**: 
     - GPIO13 - Segment 1
     - GPIO2 - Segment 2
     - GPIO7 - Segment 3
     - GPIO12 - Segment 4
     - GPIO11 - Segment 5
     - GPIO3 - Segment 6
   - **Bottom Pins (from left to right)**:
     - GPIO6 - Segment 7
     - GPIO5 - Segment 8
     - GPIO9 - Segment 9
     - GPIO4 - Segment 10
     - GPIO8 - Segment 11
     - GPIO10 - Segment 12
3. **Connect the Buttons**:
   - SNOOZE_PIN: GPIO 14
   - MODE_PIN: GPIO 15
   - INCREASE_PIN: GPIO 16
   - LIGHT_PIN: GPIO 17
   - Other leg of each button to ground (GND). Use pull-up resistors if necessary, although internal pull-ups in the Pico may be used.
4. **Connect the LED Light**:
   - GPIO 18 to the anode of the LED with a current-limiting resistor
   - Cathode of the LED to ground (GND)

