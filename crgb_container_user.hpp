#pragma once

#include "crgb_container.hpp"

class CRGB_Container_user
{
public:
  CRGB_Container_user() : CRGB_Container_user(nullptr) {};
  CRGB_Container_user(CRGB_Container* container) : container{container} {}
  virtual void setContainer(CRGB_Container* container)
  {
    this->container = container;
  }
protected:
  CRGB_Container* container;
};  