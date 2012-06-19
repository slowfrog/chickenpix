#include "Resources.h"

Resources::Resources():
  Component(TYPE) {
}

Resources::~Resources() {
  // Should destroy all resources, because this object is supposed to be the owner
}

void
Resources::setObject(Kind kind, string const &name, void *object) {
  store[kind][name] = object;
}

void *
Resources::getObject(Kind kind, string const &name) {
  return store[kind][name];
}

string
Resources::toString() const {
  return "{Resources}";
}
