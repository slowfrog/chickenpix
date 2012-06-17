#include "CLVisualSprite.h"

CLVisualSprite::CLVisualSprite(CL_Sprite &sprite):
  sprite(sprite) {
}

CLVisualSprite::~CLVisualSprite() {
}

void
CLVisualSprite::render(CL_GraphicContext &gc, float x, float y) {
  sprite.draw(gc, x, y);
  sprite.update();
}

string
CLVisualSprite::toString() const {
  return "{CLVisualSprite}}";
}
