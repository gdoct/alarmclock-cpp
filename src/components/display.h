#pragma once
#include <string>

class Display {
  public:
    Display(float brightness) : brightness(brightness) {}

    virtual void clear() = 0;
    virtual void write(const std::string &str) = 0;
    void set_brightness(float brightness) { this->brightness = brightness; }
    float get_brightness() const { return brightness; }

  protected:
    float brightness;
};

