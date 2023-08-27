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

void TearPixel::setContainer(CRGB_Container* container)
{
  this->container = container;
  if (this->container != nullptr) {
    this->current_max_lenght = *(this->container)[this->current.strip].lenght() - 1;
  }
}

void TearPixel::initVariables()
{
  this->setColor(0);
  this->current = {0, 0};
  if (this->container != nullptr) this->setStart({0, 0});
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

const Connect& TearPixel::checkConnect(const PixelPos& pos)
{
  if (this->connections_buffer != nullptr) {
    uint16_t j{0};
    Connect connect{false};
    for (uint16_t i = 0; i < this->connections_number; ++i) {
      if ((connect = (this->strips_connections[i] | pos))) this->connections_buffer[j++] = connect;
    }
    if (j == 0) return this->no_connetions;
    else return this->connections_buffer[random(j)];
  } else return this->no_connetions;
}

const Connect& TearPixel::checkConnect()
{
  return this->checkConnect(this->current);
}

void TearPixel::jumpOnPos(const PixelPos& pos)
{
  this->preview = this->current;
  this->current = pos;
  if (this->container != nullptr) {
    this->current_max_lenght = *(this->container)[pos.strip].lenght() - 1;
  }
}

void TearPixel::nextStep()
{
  if (this->container != nullptr) {
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
}
