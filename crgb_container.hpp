#pragma once

#include "crgb_buffer.hpp"
#include "crgb_structures.hpp"

class CRGB_Container
{
public:
  CRGB_Container() : buffer{nullptr}, size{0} {}
  CRGB_Container(CRGB_buffer* crgb_buffer_array, uint16_t array_size)
  : buffer{crgb_buffer_array}, size{array_size} {}

  void add_CRGB_buffer(CRGB_buffer* crgb_buffer_array, uint16_t array_size)
  {
    this->buffer = crgb_buffer_array;
    this->size = array_size;
  }

  const uint16_t& getStripNumber() const
  {
    return this->size;
  }

  const uint16_t& getStripSize(const uint16_t index) const
  {
    return this->buffer[index].lenght();
  }

  CRGB& operator[] (const PixelPos& pos)
  {
    return this->buffer[pos.strip][pos.pixel];
  }
  
  CRGB_buffer& operator[] (const uint16_t& index)
  {
    return this->buffer[index];
  }

private:
  CRGB_buffer*  buffer;
  uint16_t      size;
};
