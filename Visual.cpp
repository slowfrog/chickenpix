#include <sstream>
#include "Visual.h"

Visual::Visual(ImgId img):
  Component(TYPE), img(img), x(-1), y(-1), w(-1), h(-1) {
}

Visual::Visual(ImgId img, int x, int y, int w, int h):
  Component(TYPE), img(img), x(x), y(y), w(w), h(h) {
}

Visual::~Visual() {
}

string
Visual::toString() const {
  ostringstream out;
  out << "{Visual img=" << img << ", x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << "}";
  return out.str();
}
