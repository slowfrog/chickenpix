#include <iostream>
#include <sstream>

#include "Scriptable.h"
#include "ComponentRegistry.h"

Component::Type
Scriptable::TYPE = SCRIPTABLE_TYPE;

Scriptable::Scriptable(string const &name):
  Component(TYPE), name_(name), initDone_(false), exitDone_(false) {
}

Scriptable::~Scriptable() {
}

void
Scriptable::update(int now) {
}

string
Scriptable::toString() const {
  ostringstream out;
  out << "{Scriptable name=" << name_ << ", init:" << initDone_ << ", exit:" << exitDone_ << "}" << ends;
  return out.str();
}
