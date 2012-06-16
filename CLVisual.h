#pragma once

#include <ClanLib/display.h>

#include "Component.h"

class CLVisual: public Component {
private:
  bool containsSprite;
  CL_Sprite *sprite;
  CL_Image *image;

public:
  static const Type TYPE = CLVISUAL_TYPE;
  
  CLVisual(CL_Sprite *sprite);
  CLVisual(CL_Image *image);
  virtual ~CLVisual();
  bool isSprite() const;
  CL_Sprite *getSprite() const;
  CL_Image *getImage() const;
  virtual string toString() const;
};

