#pragma once

#include "../../crgb_container_user.hpp"

class WavePixels : public CRGB_Container_user
{
public:
  WavePixels();
  WavePixels(CRGB_Container* container);
  ~WavePixels();
  void        setWaveColor(uint32_t color);
  void        setWaveColor(uint32_t color, uint16_t index) { this->colors[index] = color; }
  void        setContainer(CRGB_Container* container) override;
  void        resetDone(bool done) { this->done = done; }
  const bool& isDone() const { return this->done; }
  void        reset(bool reverse);
  void        nextStep(bool reverse);

private:
  void        initVariables();
  void        redefColors();
  void        redefPixelsPos();
  uint16_t*   pixels_pos;
  uint32_t*   colors;
  bool        done;
};