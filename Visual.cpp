#include <sstream>
#include "Visual.h"

Visual::Visual(ImgId img):
  Component(TYPE), part(img, -1, -1, -1, -1) {
}

Visual::Visual(ImgId img, int x, int y, int w, int h):
  Component(TYPE), part(img, x, y, w, h) {
}

Visual::~Visual() {
}

string
Visual::toString() const {
  ostringstream out;
  out << "{Visual img=" << part.img << ", x=" << part.x << ", y=" << part.y <<
    ", w=" << part.w << ", h=" << part.h << "}" << ends;
  return out.str();
}
