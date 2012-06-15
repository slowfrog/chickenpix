#include <sstream>
#include "Entity.h"

Entity::Entity(Id id):
  id(id) {
}

Entity::~Entity() {
}

void
Entity::addComponent(Component const &c) {
  comp.push_back(c);
}

void
Entity::removeComponent(Component::Type t) {
  for (vector<Component>::iterator it = comp.begin(); it < comp.end(); it++) {
    if (it->getType() == t) {
      comp.erase(it);
      break;
    }
  }
}

string
Entity::toString() const {
  ostringstream out;
  out << "<Entity id=" << id << " comp=[";
  for (vector<Component>::const_iterator it = comp.begin(); it < comp.end(); it++) {
    if (it != comp.begin()) {
      out << ", ";
    }
    out << it->toString();
  }
  out << "]>" << endl;
  return out.str();
}
