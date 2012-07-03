#include <sstream>
#include "Component.h"

Component::Component(Type type):
  type_(type) {
}

Component::~Component() {
}

string
Component::toString() const {
  ostringstream out;
  out << "{type=" << type_ << "}" << ends;
  return out.str();
}
