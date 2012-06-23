#pragma once
#include "../BVisual.h"

class CLVisualSprite: public BVisual {
private:
  CL_Sprite *sprite;
  
public:
  CLVisualSprite(CL_Sprite *sprite);
  virtual ~CLVisualSprite();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  
  virtual string toString() const;
};
