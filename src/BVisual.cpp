#include "BVisual.h"

BVisual::BVisual():
  Component(TYPE) {
}

BVisual::~BVisual() {
}

string
BVisual::toString() const {
  return "{BVisual}";
}
