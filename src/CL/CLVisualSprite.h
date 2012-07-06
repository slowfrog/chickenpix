#pragma once
#include "../BVisual.h"

class CLVisualSprite: public BVisual {
private:
  CL_Sprite *sprite;
  
public:
  CLVisualSprite(CL_Sprite *sprite);
  virtual ~CLVisualSprite();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual void debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  virtual string toString() const;
};
