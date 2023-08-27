#pragma once

#include <Arduino.h>

struct PixelPos
{
  uint16_t strip;
  uint16_t pixel;

  bool operator==(const PixelPos& other)
  {
    return (strip == other.strip) && (pixel == other.pixel);
  }

  bool operator!=(const PixelPos& other)
  {
    return !(*this == other);
  }

  bool operator>(const PixelPos& other)
  {
    return (other.strip > strip) || (other.strip == strip && other.pixel > pixel);
  }

  bool operator<(const PixelPos& other)
  {
    return (other.strip < strip) || (other.strip == strip && other.pixel < pixel);
  }

  bool operator>=(const PixelPos& other)
  {
    return (other.strip > strip) || (other.strip == strip && other.pixel >= pixel);
  }

  bool operator<=(const PixelPos& other)
  {
    return (other.strip < strip) || (other.strip == strip && other.pixel <= pixel);
  }
};

struct Connect
{
  bool connect; 
  PixelPos pos;

  explicit operator bool() { return this->connect; }
};

struct Connection2Strips
{
  PixelPos first;
  PixelPos second;

  Connect operator| (const PixelPos& pos)
  {
    if (first == pos) return {true, second};
    else if (second == pos) return {true, first};
    return {false};
  }
};

