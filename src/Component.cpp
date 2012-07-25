#include <sstream>
#include "Component.h"
#include "ComponentRegistry.h"

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

const char *
Component::getTypeName() const {
  return ComponentName[type_];
}
