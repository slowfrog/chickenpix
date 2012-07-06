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

  // For debugging: show a red outline
  CL_Draw::box(gc, x, y, x + getWidth(vc), y + getHeight(vc),
               CL_Colorf(1.0f, 0.0f, 0.0f, 0.3f));
}

int
CLVisualSprite::getWidth(VisualContext &) const {
  return sprite->get_width();
}

int
CLVisualSprite::getHeight(VisualContext &) const {
  return sprite->get_height();
}

string
CLVisualSprite::toString() const {
  return "{CLVisualSprite}}";
}
