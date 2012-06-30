#pragma once
#include "Component.h"

class Mobile: public Component {
private:
  float dx_;
  float dy_;
  
public:
  static const Type TYPE = MOBILE_TYPE;
  
  Mobile();
  Mobile(float dx, float dy);
  virtual ~Mobile();

  void setSpeed(float dx, float dy) {
    dx_ = dx;
    dy_ = dy;
  }

  float getSpeedX() const {
    return dx_;
  }

  float getSpeedY() const {
    return dy_;
  }
  virtual string toString() const;
};
