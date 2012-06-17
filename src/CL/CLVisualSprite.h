#pragma once

#include "CLVisual.h"

class CLVisualSprite: public CLVisual {
private:
  CL_Sprite &sprite;
  
public:
  CLVisualSprite(CL_Sprite &sprite);
  virtual ~CLVisualSprite();

  virtual void render(CL_GraphicContext &gc, float x, float y);
  
  virtual string toString() const;
};
