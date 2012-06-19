#pragma once

#include <ClanLib/display.h>
#include "BVisual.h"

class CLVisualSprite: public BVisual {
private:
  CL_Sprite &sprite;
  
public:
  CLVisualSprite(CL_Sprite &sprite);
  virtual ~CLVisualSprite();

  virtual void draw(VisualContext &vc, float x, float y);
  
  virtual string toString() const;
};
