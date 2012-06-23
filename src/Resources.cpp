#include "Resources.h"

CPColor
CPColor::White(255, 255, 255);

Resources::Resources():
  Component(TYPE) {
}

Resources::~Resources() {
  // Should destroy all resources, because this object is supposed to be the owner
}

void
Resources::setObject(Kind kind, string const &name, ResBase *object) {
  store[kind][name] = object;
}

ResBase *
Resources::getObject(Kind kind, string const &name) {
  return store[kind][name];
}

string
Resources::toString() const {
  return "{Resources}";
}
