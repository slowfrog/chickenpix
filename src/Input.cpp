#include "Input.h"

Input::Input():
  Component(TYPE), state_(NULL) {
}

Input::~Input() {
}

string
Input::toString() const {
  return string("{Input}");
}
