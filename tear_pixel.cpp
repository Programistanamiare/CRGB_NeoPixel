#include "tear_pixel.hpp"

TearPixel::TearPixel() : TearPixel(nullptr) {}

TearPixel::TearPixel(CRGB_Container* container)
: CRGB_Container_user{container}
{
  this->initVariables();
}

TearPixel::~TearPixel()
{
  if (this->connections_buffer != nullptr) delete[] this->connections_buffer;
}

void TearPixel::initVariables()
{
  this->setColor(0);
  this->setStart({0, 0});
  this->connections_number = 0;
  this->connections_buffer = nullptr;
}

void TearPixel::setStripsConnections(Connection2Strips* strp_con_arr, uint16_t ara_len)
{
  this->strips_connections = strp_con_arr;
  if (this->connections_number != ara_len) {
    if (this->connections_buffer != nullptr) delete[] this->connections_buffer;
    this->connections_buffer = new Connect[ara_len];
    this->connections_number = ara_len;
  }
}

Connect& TearPixel::checkConnect(const PixelPos& pos)
{
  uint16_t j{0};
  Connect connect{false};
  this->connections_buffer[0] = connect;
  for (uint16_t i = 0; i < this->connections_number; ++i) {
    if ((connect = (this->strips_connections[i] | pos))) this->connections_buffer[j++] = connect;
  }
  if (j < 2) return this->connections_buffer[0];
  else return this->connections_buffer[random(j)];
}

Connect& TearPixel::checkConnect()
{
  return this->checkConnect(this->current);
}

void TearPixel::jumpOnPos(const PixelPos& pos)
{
  this->preview = this->current;
  this->current = pos;
}

void TearPixel::nextStep()
{
  Connect connect = this->checkConnect();
  if (connect && this->preview.strip == this->current.strip && 
      (this->current.pixel == 0 || this->current.pixel == this->current_max_lenght || !random(3))) {
      this->jumpOnPos(connect.pos);
      this->step = random(2) ? -1 : 1;
      if (this->current.pixel == 0) this->step = 1;
      else if (this->current.pixel == this->current_max_lenght) this->step = -1;
  } else {
    if (this->current.pixel == 0) this->step = 1;
    else if (this->current.pixel == this->current_max_lenght) this->step = -1;
    this->preview = this->current;
    this->current.pixel += this->step;
  }
  (*this->container)[this->preview] = 0;
  (*this->container)[this->current] = this->color;
}
