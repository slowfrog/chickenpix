#pragma once
#include "Component.h"

class Transform: public Component {
private:
  float x;
  float y;
  
public:
  static const Type TYPE = TRANSFORM_TYPE;
  
  Transform(float x, float y);
  virtual ~Transform();
  inline float getX() const {
    return x;
  }
  inline float getY() const {
    return y;
  }

  virtual string toString() const;
};
