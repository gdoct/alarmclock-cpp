#pragma once

#include "components/display.h"
#include "model.h"
#include "time/clock.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>

class AlarmClockView : public Display {
public:
  AlarmClockView(Display *display)
      : Display(display->get_brightness()), display(display),
        display_brightness_direction(1){}

  void  clear(void);
  void  update(AlarmClockState* model, Time &current_time);
  void  increase_brightness(void);
  float get_brightness(void) const;
  void  set_brightness(const float &brightness);

private:
  Display *display;
  int display_brightness_direction;
  void write(const std::string &text);
};

