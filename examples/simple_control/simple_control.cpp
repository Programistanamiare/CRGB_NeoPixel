#include "../../CRGB_NeoPxiel.h"

#define STRIP_NUM 3
#define COLOR 0x00FF00

// create 3 strips
CRGB_buffer strips[STRIP_NUM] =
{
  {10}, {20}, {15} // setting the length of each led strip
};

// create container for strips
CRGB_Container container(strips, STRIP_NUM);

void setup()
{
  // in template argument set strip data pin.
  strips[0].setup<2>();
  strips[1].setup<3>();
  strips[2].setup<4>();
}

void loop()
{

  // sequential switching on of the LED pixels in green.
  for (uint16_t i = 0; i < STRIP_NUM; ++i) {
    for (uint16_t j = 0; j < strips[i].lenght; ++j) {
      container[i][j] = COLOR;
      FastLED.show();
      delay(100);
    }
  }
  delay(2000);

  // sequential switching off of the LED pixels.
  for (uint16_t i = STRIP_NUM - 1; i >= 0; --i) {
    for (uint16_t j = strips[i].lenght - 1; j >= 0; --j) {
      container[i][j] = 0;
      FastLED.show();
      delay(100);
    }
  }
  delay(2000);
}