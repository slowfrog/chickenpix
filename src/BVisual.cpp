#include "BVisual.h"

BVisual::BVisual(int zOrder, bool gui):
  Component(TYPE), zOrder_(zOrder), gui_(gui) {
}

BVisual::~BVisual() {
}

bool
BVisual::compareZOrder(BVisual const &visual1, BVisual const &visual2) {
  return visual1.zOrder_ < visual2.zOrder_;
}

string
BVisual::toString() const {
  return "{BVisual}";
}
