#pragma once

#include <Arduino.h>
#include "FastLED/FastLED.h"

class CRGB_buffer
{
public: 
  CRGB_buffer(uint16_t lenght) : _lenght{lenght}
  {
    this->_leds = new CRGB[_lenght];
  }
  ~CRGB_buffer()
  {
    if (this->_leds != nullptr) delete[] this->_leds;
  }

  CRGB& operator[] (const uint16_t& index)
  {
    return this->_leds[index];
  }

  const uint16_t& lenght() const
  {
    return this->_lenght;
  }

  template<uint8_t data_pin>
  void setup() 
  {
    FastLED.addLeds<NEOPIXEL, data_pin>(this->_leds, this->_lenght);
  }

private:
  uint16_t  _lenght;
  CRGB*     _leds;
};

