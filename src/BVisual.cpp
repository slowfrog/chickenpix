#include <sstream>
#include "BVisual.h"

BVisual::BVisual(ImgId img):
  Component(TYPE), part(img, -1, -1, -1, -1) {
}

BVisual::BVisual(ImgId img, int x, int y, int w, int h):
  Component(TYPE), part(img, x, y, w, h) {
}

BVisual::~BVisual() {
}

string
BVisual::toString() const {
  ostringstream out;
  out << "{BVisual img=" << part.img << ", x=" << part.x << ", y=" << part.y <<
    ", w=" << part.w << ", h=" << part.h << "}" << ends;
  return out.str();
}
