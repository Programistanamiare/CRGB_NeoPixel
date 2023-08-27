#include "wave_pixels.hpp"

WavePixels::WavePixels() : WavePixels(nullptr) {}

WavePixels::WavePixels(CRGB_Container* container) : CRGB_Container_user{container}
{
  this->initVariables();
}

WavePixels::~WavePixels()
{
  if (this->colors != nullptr) delete[] this->colors;
  if (this->pixels_pos != nullptr) delete[] this->pixels_pos;
}

void WavePixels::initVariables()
{
  this->colors = nullptr;
  this->pixels_pos = nullptr;
  this->done = false;
  this->redefPixelsPos();
  this->redefColors();
}

void WavePixels::redefColors()
{
  if (this->container != nullptr) {
    if (this->colors != nullptr) delete[] this->colors;
    this->colors = new uint32_t[this->container->lenght()];
    this->setWaveColor(0xFFFFFF);
  }
}

void WavePixels::redefPixelsPos()
{
  if (this->container != nullptr) {
    if (this->pixels_pos != nullptr) delete[] this->pixels_pos;
    this->pixels_pos = new uint16_t[this->container->lenght()];
    for (uint16_t i = 0; i < this->container->lenght(); ++i) this->pixels_pos = 0;
  }
}

void WavePixels::setContainer(CRGB_Container* container) 
{
  this->container = container;
  this->redefColors();
  this->redefPixelsPos();
}

void WavePixels::setWaveColor(uint32_t color)
{
  for (uint16_t i = 0; i < this->container->lenght(); ++i) this->colors[i] = color;
}

void WavePixels::reset(bool reverse)
{
  for (uint16_t i = 0; i < this->container->lenght(); ++i)
  this->pixels_pos[i] = reverse ? (*this->container)[i].lenght() - 1 : 0;
  this->done = false;
}

void WavePixels::nextStep(bool reverse)
{
  if (!this->done && this->container != nullptr) {
    uint16_t all = 0;
    for (uint16_t i = 0; i < this->container->lenght(); ++i) {
      if (reverse) {
        if (this->pixels_pos[i] > 0) this->pixels_pos[i] -= 1;
        else all++;
      } else {
        if (this->pixels_pos[i] < this->container->getStripLenght(i)) this->pixels_pos[i] += 1;
        else all++;
      }
    }
    this->done = (all == this->container->lenght());
  }
}