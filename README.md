# Raspberry Pi Pico Wakeup light Project

This example project demonstrates how to use a 5461AS-1 4-digit 7-segment display with a Raspberry Pi Pico, 4 buttons, a bunch of resistors and an RGB led, to build a retro alarmclock with wake-up light.

## Building the project
make sure the pico sdk is installed from https://github.com/raspberrypi/pico-sdk 
```
$ cmake -DCMAKE_BUILD_TYPE=Release .
$ make clean && make
```

the resulting elf and uf2 binaries will be placed in the folder "target". connect 
the pico while holding down boot-select and copy the uf2 file to the pico. Debug 
output is available through a serial over usb connection.

## Components and Pins

![Breadboard layout](https://github.com/gdoct/alarmclock-cpp/blob/master/docs/breadboard.png "Breadboard image")
### Raspberry Pi Pico GPIO Connections

#### 7-Segment Display Connections
- GPIO15 - Segment 1
- GPIO14 - Segment 2
- GPIO13 - Segment 3
- GPIO12 - Segment 4
- GPIO11 - Segment 5
- GPIO10 - Segment 6

**Bottom Pins (from left to right):**
- GPIO16 - Segment 7
- GPIO17 - Segment 8
- GPIO18 - Segment 9
- GPIO19 - Segment 10
- GPIO20 - Segment 11
- GPIO21 - Segment 12

#### Control Buttons
- **SNOOZE_PIN**: GPIO 14
- **MODE_PIN**: GPIO 15
- **INCREASE_PIN**: GPIO 16
- **LIGHT_PIN**: GPIO 17

#### LED Light
- **LED**: GPIO 5-7 (with a 220 ohm current-limiting resistor)

## Breadboard Layout
![Component layout](https://github.com/gdoct/alarmclock-cpp/blob/master/docs/physical_layout.png "Component layout")

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
4. **Connect the RGB LED Light**:
   - GPIO 5-7 to the anodes of the  RGBLED with a 220 ohm current-limiting resistor
   - Cathode of the LED to ground (GND)

