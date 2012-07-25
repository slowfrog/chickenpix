#include "Input.h"
#include "ComponentRegistry.h"

Component::Type
Input::TYPE = INPUT_TYPE;

Input::Input():
  Component(TYPE), state_(NULL) {
}

Input::~Input() {
}

string
Input::toString() const {
  return string("{Input}");
}
