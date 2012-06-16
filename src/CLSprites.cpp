#include <sstream>
#include "CLSprites.h"

CLSprites::CLSprites():
  Component(TYPE) {
}

CLSprites::~CLSprites() {
  // Should delete all sprites and images
  images.clear();
  sprites.clear();
}

void
CLSprites::addImage(string const &name, CL_Image *image) {
  images[name] = image;
}

CL_Image *
CLSprites::getImage(string const &name) {
  return images[name];
}

void
CLSprites::addSprite(string const &name, CL_Sprite *sprite) {
  sprites[name] = sprite;
}

CL_Sprite *
CLSprites::getSprite(string const &name) {
  return sprites[name];
}

string
CLSprites::toString() const {
  ostringstream out;
  out << "{Sprites images=" << images.size() << " sprites=" << sprites.size() << "}" << ends;
  return out.str();
}
