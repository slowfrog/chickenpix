/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once
#include "Component.h"

class Camera: public Component {
private:
  float offsetX_;
  float offsetY_;
  unsigned int width_;
  unsigned int height_;
public:
  static Type TYPE;
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
