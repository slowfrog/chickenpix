#include <sstream>
#include "log.h"
#include "Entity.h"


const Entity::Type Entity::TYPE = 1;

Entity::Entity():
  _id(INVALID_ID), _type(TYPE) {
}

Entity::Entity(Id id):
  _id(id), _type(TYPE) {
}

Entity::Entity(Entity const &src):
  _id(src._id), _type(src._type), comp(src.comp), tags(src.tags) {
  // Re-parent all components
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); ++it) {
    (*it)->setEntity(this);
  }
}

Entity::Entity(Entity const &src, Type type):
  _id(src._id), _type(type), comp(src.comp), tags(src.tags) {
  // Re-parent all components
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); ++it) {
    (*it)->setEntity(this);
  }
}

Entity::~Entity() {
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); it++) {
    delete *it;
  }
  comp.clear();
}

void
Entity::addComponent(Component *c) {
  comp.push_back(c);
  c->setEntity(this);
}

void
Entity::removeComponent(Component::Type t) {
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); it++) {
    Component *c = (*it);
    if (c->getType() == t) {
      c->setEntity(NULL);
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

/*
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
 */

void
Entity::releaseComponents() {
  comp.clear();
}

string
Entity::toString() const {
  ostringstream out;
  out << "<Entity id=" << _id << " comp=[";
  for (vector<Component *>::const_iterator it = comp.begin(); it < comp.end(); it++) {
    if (it != comp.begin()) {
      out << ", ";
    }
    out << (*it)->getType() << "-" << (*it)->toString();
  }
  out << "]>" << ends;
  return out.str();
}
