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

class MapInfo: public Component {
private:
  float minx_;
  float miny_;
  float maxx_;
  float maxy_;

public:
  static Type TYPE;
  
  MapInfo(float minx, float miny, float maxx, float maxy);
  virtual ~MapInfo();

  inline
  float getMinX() const {
    return minx_;
  }

  inline
  float getMinY() const {
    return miny_;
  }
  
  inline
  float getMaxX() const {
    return maxx_;
  }

  inline
  float getMaxY() const {
    return maxy_;
  }

  inline
  void setMinX(float minx) {
    minx_ = minx;
  }

  inline
  void setMinY(float miny) {
    miny_ = miny;
  }

  inline
  void setMaxX(float maxx) {
    maxx_ = maxx;
  }

  inline
  void setMaxY(float maxy) {
    maxy_ = maxy;
  }
  
  virtual string toString() const;
};
