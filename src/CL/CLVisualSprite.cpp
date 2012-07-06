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

void
CLVisualSprite::debugDraw(VisualContext &vc, float x, float y, int delta,
                          float left, float top, float right, float bottom) {
  // Draw base visual
  draw(vc, x, y, delta);

  // For debugging: show a red outline
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  sprite->draw(gc, x, y);
  sprite->update(delta);
  float cx = x + getWidth(vc) / 2;
  float cy = y + getHeight(vc) / 2;
  CL_Draw::box(gc, cx - left, cy - top, cx + right, cy + bottom,
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
