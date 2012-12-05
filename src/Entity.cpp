/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
}

Entity::Entity(Entity const &src, Type type):
  _id(src._id), _type(type), comp(src.comp), tags(src.tags) {
}

Entity::~Entity() {
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); it++) {
    delete *it;
  }
  comp.clear();
}

void
Entity::addComponent(Component *newComp) {
  Component::Type t = newComp->getType();
  for (vector<Component *>::iterator it = comp.begin(); it < comp.end(); it++) {
    Component *c = (*it);
    if (c->getType() == t) {
      delete c;
      *it = newComp;
      return;
    }
  }
  comp.push_back(newComp);
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
Entity::getComponent(Component::Type t) const {
  for (vector<Component *>::const_iterator it = comp.begin(); it < comp.end();
       it++) {
    if ((*it)->getType() == t) {
      return *it;
    }
  }
  return NULL;
}

bool
Entity::hasComponent(Component::Type t) const {
  for (vector<Component *>::const_iterator it = comp.begin(); it < comp.end(); it++) {
    if ( (*it)->getType() == t) {
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
