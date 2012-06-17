#include <sstream>
#include "CLResources.h"

CLResources::CLResources():
  Component(TYPE) {
}

CLResources::~CLResources() {
  // Should delete all sprites and images
  images.clear();
  sprites.clear();
  fonts.clear();
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

void
CLResources::addFont(string const &name, CL_Font *font) {
  fonts[name] = font;
}

CL_Font *
CLResources::getFont(string const &name) {
  return fonts[name];
}

string
CLResources::toString() const {
  ostringstream out;
  out << "{Sprites images=" << images.size() << " sprites=" << sprites.size() << "}" << ends;
  return out.str();
}
