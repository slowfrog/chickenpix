#include "CLVisualContext.h"
#include "CLVisualSprite.h"

CLVisualSprite::CLVisualSprite(CL_Sprite *sprite):
  sprite(sprite) {
}

CLVisualSprite::~CLVisualSprite() {
  delete sprite;
}

void
CLVisualSprite::draw(VisualContext &vc, float x, float y, int delta) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  sprite->draw(gc, x, y);
  sprite->update(delta);
}

string
CLVisualSprite::toString() const {
  return "{CLVisualSprite}}";
}
