#include <sstream>
#include "Entity.h"

Entity::Entity():
  id(INVALID_ID) {
}

Entity::Entity(Id id):
  id(id) {
}

Entity::~Entity() {
}

void
Entity::addComponent(Component *c) {
  comp.push_back(c);
}

void
Entity::removeComponent(Component::Type t) {
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); it++) {
    Component *c = (*it);
    if (c->getType() == t) {
      comp.erase(it);
      delete c;
      break;
    }
  }
}

Component *
Entity::getComponent(Component::Type t) {
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); it++) {
    if ((*it)->getType() == t) {
      return *it;
    }
  }
  throw 0;
}

bool
Entity::hasComponent(Component::Type t) const {
  for (vector<Component *>::const_iterator it = comp.begin(); it < comp.end(); it++) {
    if ((*it)->getType() == t) {
      return true;
    }
  }
  return false;
}

bool
Entity::hasComponents(Component::Type t1, Component::Type t2) const {
  return hasComponent(t1) && hasComponent(t2);
}


bool
Entity::hasTag(string const &tag) const {
  for (vector<string>::const_iterator it = tags.begin(); it < tags.end(); it++) {
    if (tag == *it) {
      return true;
    }
  }
  return false;
}

void
Entity::addTag(string const &tag) {
  if (!hasTag(tag)) {
    tags.push_back(tag);
  }
}

void
Entity::removeTag(string const &tag) {
  for (vector<string>::iterator it = tags.begin(); it < tags.end(); it++) {
    if (tag == *it) {
      tags.erase(it);
      return;
    }
  }
}

string
Entity::toString() const {
  ostringstream out;
  out << "<Entity id=" << id << " comp=[";
  for (vector<Component *>::const_iterator it = comp.begin(); it < comp.end(); it++) {
    if (it != comp.begin()) {
      out << ", ";
    }
    out << (*it)->getType() << "-" << (*it)->toString();
  }
  out << "]>" << ends;
  return out.str();
}
