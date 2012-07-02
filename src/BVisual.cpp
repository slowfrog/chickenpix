#include "BVisual.h"

BVisual::BVisual(bool gui):
  Component(TYPE), gui_(gui) {
}

BVisual::~BVisual() {
}

string
BVisual::toString() const {
  return "{BVisual}";
}
