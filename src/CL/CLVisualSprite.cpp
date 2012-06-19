#include "CLVisualContext.h"
#include "CLVisualSprite.h"

CLVisualSprite::CLVisualSprite(CL_Sprite &sprite):
  BVisual(3), sprite(sprite) {
}

CLVisualSprite::~CLVisualSprite() {
}

void
CLVisualSprite::draw(VisualContext &vc, float x, float y) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  sprite.draw(gc, x, y);
  sprite.update();
}

string
CLVisualSprite::toString() const {
  return "{CLVisualSprite}}";
}
