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
  inline void setX(float nx) {
    x = nx;
  }
  inline void setY(float ny) {
    y = ny;
  }
  inline void moveTo(float nx, float ny) {
    x = nx;
    y = ny;
  }
  inline void moveBy(float dx, float dy) {
    x += dx;
    y += dy;
  }

  virtual string toString() const;
};
