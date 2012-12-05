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

class Transform: public Component {
private:
  float x;
  float y;
  
public:
  static Type TYPE;
  
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
