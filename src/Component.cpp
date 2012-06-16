#include <sstream>
#include "Component.h"

Component::Component(Type type):
  type(type) {
}

Component::~Component() {
}

string
Component::toString() const {
  ostringstream out;
  out << "{type=" << type << "}" << ends;
  return out.str();
}
