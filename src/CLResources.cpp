#include <sstream>
#include "CLResources.h"

CLResources::CLResources():
  Component(TYPE) {
}

CLResources::~CLResources() {
  // Should delete all sprites and images
  images.clear();
  sprites.clear();
}

void
CLResources::addImage(string const &name, CL_Image *image) {
  images[name] = image;
}

CL_Image *
CLResources::getImage(string const &name) {
  return images[name];
}

void
CLResources::addSprite(string const &name, CL_Sprite *sprite) {
  sprites[name] = sprite;
}

CL_Sprite *
CLResources::getSprite(string const &name) {
  return sprites[name];
}

string
CLResources::toString() const {
  ostringstream out;
  out << "{Sprites images=" << images.size() << " sprites=" << sprites.size() << "}" << ends;
  return out.str();
}
