#include <sstream>
#include "EntityManager.h"

EntityManager::EntityManager(string const &name):
  name(name), entities(1) {
}

EntityManager::~EntityManager() {
  entities.clear();
}

Entity *
EntityManager::createEntity() {
  unsigned int i;
  Entity *ent;
  for (i = 1; i < entities.size(); ++i) {
    ent = entities[i];
    if (ent == NULL) {
      ent = new Entity(i);
      entities[i] = ent;
      return ent;
    }
  }
  ent = new Entity(i);
  entities.push_back(ent);
  return ent;
}

Entity *
EntityManager::getEntity(Entity::Id id) {
  if ((id > 0) && (id < entities.size())) {
    return entities[id];
  }
  throw string("No such entity to get");
}

void
EntityManager::destroyEntity(Entity::Id id) {
  if ((id > 0) && (id < entities.size())) {
    delete entities[id];
    entities[id] = NULL;
  } else {
    throw string("No such entity to destroy");
  }
}

void
EntityManager::destroyEntity(Entity *entity) {
  destroyEntity(entity->getId());
}

vector<Entity *>
EntityManager::getEntities(Component::Type t) {
  vector<Entity *> ret;
  for (unsigned int i = 1; i < entities.size(); ++i) {
    Entity *ent = entities[i];
    if ((ent != NULL) && (ent->hasComponent(t))) {
      ret.push_back(ent);
    }
  }
  return ret;
}

vector<Entity *>
EntityManager::getEntities(Component::Type t1, Component::Type t2) {
  vector<Entity *> ret;
  for (unsigned int i = 1; i < entities.size(); ++i) {
    Entity *ent = entities[i];
    if ((ent != NULL) && (ent->hasComponents(t1, t2))) {
      ret.push_back(ent);
    }
  }
  return ret;
}

Entity *
EntityManager::getEntity(Component::Type t) {
  for (unsigned int i = 1; i < entities.size(); ++i) {
    Entity *ent = entities[i];
    if ((ent != NULL) && (ent->hasComponent(t))) {
      return ent;
    }
  }
  return NULL;
}

string
EntityManager::toString() const {
  ostringstream out;
  out << "{EntityManager name=" << name << ", entities[";
  for (unsigned int i = 1; i < entities.size(); ++i) {
    if (entities[i] != NULL) {
      out << "@";
    } else {
      out << ".";
    }
  }
  out << "]}" << ends;
  return out.str();
}
