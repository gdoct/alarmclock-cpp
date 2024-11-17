#pragma once
#ifndef ALARMCLOCKMODEL_H
#define ALARMCLOCKMODEL_H

#include "state.h"
#include "util/logger.h"
#include <memory>

const std::vector<std::string> AlarmClockStateNames = {
    "blank",          "display time",     "set hour", "set minute",
    "set alarm hour", "set alarm minute", "alarm"};

class AlarmClockModel {
  public:
    AlarmClockModel(void);
    int increment_mode(void);
    bool check_alarm(void);
    void raise_alarm(void);
    void increase_value(void);
//    AlarmClockState get_state();
    std::unique_ptr<AlarmClockState> get_state();
  private:
    AlarmClockState state;
};

#endif // ALARMCLOCKMODEL_H
