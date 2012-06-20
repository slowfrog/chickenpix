#include <iostream>
#include <sstream>

#include "Scriptable.h"

Scriptable::Scriptable(string const &name):
  Component(TYPE), name(name) {
}

Scriptable::~Scriptable() {
}

void
Scriptable::update(int now) {
  cout << "." << flush;
}

string
Scriptable::toString() const {
  ostringstream out;
  out << "{Scriptable name=" << name << "}" << ends;
  return out.str();
}
