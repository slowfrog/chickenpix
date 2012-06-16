#include <sstream>
#include "CLVisual.h"

CLVisual::CLVisual(CL_Sprite *sprite):
  Component(TYPE), containsSprite(true), sprite(sprite), image(NULL) {
}

CLVisual::CLVisual(CL_Image *image):
  Component(TYPE), containsSprite(false), sprite(NULL), image(image) {
}

CLVisual::~CLVisual() {
}

bool
CLVisual::isSprite() const {
  return containsSprite;
}

CL_Sprite *
CLVisual::getSprite() const {
  return sprite;
}

CL_Image *
CLVisual::getImage() const {
  return image;
}

string
CLVisual::toString() const {
  ostringstream out;
  out << "{CLVisual type=" << (containsSprite ? "sprite" : "image") << "}" << ends;
  return out.str();
}
