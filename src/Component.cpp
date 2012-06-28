#include <sstream>
#include "Component.h"

Component::Component(Type type):
  _type(type) {
}

Component::~Component() {
}

string
Component::toString() const {
  ostringstream out;
  out << "{type=" << _type << "}" << ends;
  return out.str();
}
