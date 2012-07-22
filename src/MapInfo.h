#pragma once

#include "Component.h"

class MapInfo: public Component {
private:
  float minx_;
  float miny_;
  float maxx_;
  float maxy_;

public:
  static const Type TYPE = MAPINFO_TYPE;
  
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
