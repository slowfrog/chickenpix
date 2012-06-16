#include <sstream>
#include "CLSprites.h"

CLSprites::CLSprites():
  Component(TYPE) {
}

CLSprites::~CLSprites() {
  resources.clear();
}

void
CLSprites::addSprite(string const &name, CL_Sprite *sprite) {
  resources[name] = sprite;
}

CL_Sprite *
CLSprites::getSprite(string const &name) {
  return resources[name];
}

string
CLSprites::toString() const {
  ostringstream out;
  out << "{Sprites size=" << resources.size() << "}" << ends;
  return out.str();
}
