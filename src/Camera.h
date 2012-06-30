#pragma once
#include "Component.h"

class Camera: public Component {
private:
  float offsetX_;
  float offsetY_;
public:
  static const Type TYPE = CAMERA_TYPE;
  Camera();
  Camera(float offsetX, float offsetY);
  virtual ~Camera();

  inline
  float getOffsetX() const {
    return offsetX_;
  }

  inline float getOffsetY() const {
    return offsetY_;
  }

  inline void setOffsetX(float offsetX) {
    offsetX_ = offsetX;
  }

  inline void setOffsetY(float offsetY) {
    offsetY_ = offsetY;
  }
  
  virtual string toString() const;
};
