#pragma once
#ifndef ALARMCLOCKVIEW_H
#define ALARMCLOCKVIEW_H

#include "components/display.h"
#include "model.h"
#include "util/clockfunctions.h"
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

  void update(AlarmClockModel &model, Time &current_time);
  void increase_brightness();
  void write(const std::string &text);
  void clear();
  void set_brightness(float brightness);
  float get_brightness() const;

private:
  Display *display;
  int display_brightness_direction;
};

#endif // ALARMCLOCKVIEW_H
