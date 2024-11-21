#pragma once

#include "state.h"
#include "util/logger.h"
#include <memory>

class AlarmClockModel {
  public:
    AlarmClockModel(void);
    ~AlarmClockModel();
    int increment_mode(void);
    bool check_alarm(void);
    void raise_alarm(void);
    void increase_value(void);
    AlarmClockState* get_state() const;
  private:
    AlarmClockState *state;
};
