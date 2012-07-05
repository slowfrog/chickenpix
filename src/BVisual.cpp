#include "BVisual.h"

BVisual::BVisual(float cx, float cy, int zOrder, bool gui):
  Component(TYPE), cx_(cx), cy_(cy), zOrder_(zOrder), gui_(gui) {
}

BVisual::BVisual(int zOrder, bool gui):
  Component(TYPE), cx_(0), cy_(0), zOrder_(zOrder), gui_(gui) {
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
