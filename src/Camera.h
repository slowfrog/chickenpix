#pragma once
#include "Component.h"

class Camera: public Component {
private:
  float offsetX_;
  float offsetY_;
  unsigned int width_;
  unsigned int height_;
public:
  static const Type TYPE = CAMERA_TYPE;
  Camera();
  Camera(float offsetX, float offsetY, unsigned int width, unsigned int height);
  virtual ~Camera();

  inline
  float getOffsetX() const {
    return offsetX_;
  }

  inline float getOffsetY() const {
    return offsetY_;
  }

  inline unsigned int getWidth() const {
    return width_;
  }

  inline unsigned int getHeight() const {
    return height_;
  }
  
  inline void setOffsetX(float offsetX) {
    offsetX_ = offsetX;
  }

  inline void setOffsetY(float offsetY) {
    offsetY_ = offsetY;
  }

  inline void setWidth(unsigned int width) {
    width_ = width;
  }

  inline void setHeight(unsigned int height) {
    height_ = height;
  }
  
  virtual string toString() const;
};
