#pragma once

#include "crgb_container_user.hpp"


class TearPixel : public CRGB_Container_user
{
public:
  TearPixel();
  TearPixel(CRGB_Container* container);
  ~TearPixel();
  void                setStripsConnections(Connection2Strips* strips_connections_array, uint16_t connections_number);
  void                setStart(PixelPos pos) { this->current = this->preview = pos; }
  void                setColor(uint32_t color) { this->color = color; }
  const PixelPos&     getCurrentPos() const { return this->current; }
  const PixelPos&     getPreviewPos() const { return this->preview; }
  void                jumpOnPos(const PixelPos& pos);
  void                nextStep();

private:
  Connect&            checkConnect();
  Connect&            checkConnect(const PixelPos& pos);
  void                initVariables();
  uint8_t             step;
  uint32_t            color;
  PixelPos            current;
  uint16_t            current_max_lenght;
  PixelPos            preview;
  Connection2Strips*  strips_connections;
  uint16_t            connections_number;
  Connect*            connections_buffer;
}; 