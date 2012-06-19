#include <sstream>
#include "BVisual.h"

BVisual::BVisual():
  Component(TYPE), part(-1, -1, -1, -1) {
}

BVisual::BVisual(int x, int y, int w, int h):
  Component(TYPE), part(x, y, w, h) {
}

BVisual::~BVisual() {
}

string
BVisual::toString() const {
  ostringstream out;
  out << "{BVisual x=" << part.x << ", y=" << part.y <<
    ", w=" << part.w << ", h=" << part.h << "}" << ends;
  return out.str();
}
