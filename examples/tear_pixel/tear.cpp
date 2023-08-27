#include "../../CRGB_NeoPxiel.h"
#include "tear_pixel.hpp"

#define STRIPS_NUM              4
#define TEARS_NUM               2
#define STRIPS_CONNECTIONS_NUM  3
#define TEAR_COLOR              0xFF00FF

// create 4 strips.
CRGB_buffer strips[STRIPS_NUM] =
{
  {50}, {30}, {90}, {100} 
};

// create strips container.
CRGB_Container container(strips, STRIPS_NUM);

// create tears array.
TearPixel tears[TEARS_NUM];

/*
  
  An illustrative sketch of the (example) physical arrangement of the led strips.
  
  |   <- [strip index][pixel index]

  [0][0] -> ########...########## <- [0][49]
                                # <- [1][0]
                                #
                                #
                                # 
                                # [3][0]
                              ... |
                                # v
                     [1][40] -> # #####...### <- [3][29]
                                #
                              ...
                                #
                                # <- [1][89]       
                     [2][99] -> ###########...########## <- [2][0] 
                                                     
*/

// create strips connections array.
Connection2Strips connections[STRIPS_CONNECTIONS_NUM] =
{
  {0, 49, 1, 0},    // 0 strip index connected at 49 (last) pixel index with 1 strip index at 0 (first) pixel index,
  {1, 40, 2, 0},    // 1 strip index connected at 40 pixel index with 2 strip index at 0 (first) pixel index,
  {1, 89, 3, 99}    // 1 strip index connected at 89 (last) pixel index with 3 strip index at 99 (last) pixel index.
};


void setup()
{
  // in template argument set strip data pin.
  strips[0].setup<2>();
  strips[1].setup<5>();
  strips[2].setup<7>();

  // setup all tears.
  for (uint16_t i = 0; i < TEARS_NUM; ++i) {
    tears[i].setContainer(&container);
    tears[i].setColor(TEAR_COLOR);
    tears[i].setStart({i, 0});
    tears[i].setStripsConnections(connections, STRIPS_CONNECTIONS_NUM);
  }
}

void setup()
{
  // step by step for all tears
  for (uint16_t i = 0; i < TEARS_NUM; ++i) {
    tears[i].nextStep();
  }
  FastLED.show();
  delay(50);
}