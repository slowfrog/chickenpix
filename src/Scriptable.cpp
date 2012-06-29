#include <iostream>
#include <sstream>

#include "Scriptable.h"

Scriptable::Scriptable(string const &name):
  Component(TYPE), _name(name), _initDone(false), _exitDone(false) {
}

Scriptable::~Scriptable() {
}

void
Scriptable::update(int now) {
}

string
Scriptable::toString() const {
  ostringstream out;
  out << "{Scriptable name=" << _name << ", init:" << _initDone << ", exit:" << _exitDone << "}" << ends;
  return out.str();
}
