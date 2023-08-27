#include "../../CRGB_NeoPxiel.h"
#include "wave_pixels.hpp"

#define STRIPS_NUM  3
#define WAVE_COLOR  0x0000FF

// create 3 strips
CRGB_buffer strips[STRIPS_NUM] = 
{
  {50}, {70}, {30} // setting the length of each led strip
};

// create container for strips
CRGB_Container container(strips, STRIPS_NUM);


WavePixels wave(&container);

bool reverse;

void setup()
{
  strips[0].setup<2>();
  strips[1].setup<5>();
  strips[2].setup<3>();
  wave.setWaveColor(WAVE_COLOR);
  reverse = false;
}

void loop()
{
  while(!wave.isDone()) {
    wave.nextStep(reverse);
    FastLED.show();
    delay(50);
  }
  wave.resetDone(false);
  reverse = !reverse;
}