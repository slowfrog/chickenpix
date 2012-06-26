#include <sstream>
#include "EntityManager.h"

EntityManager::EntityManager(string const &name):
  name(name), entities(1) {
}

EntityManager::~EntityManager() {
  entities.clear();
}

string
EntityManager::getName() const {
  return name;
}

int
EntityManager::getSize() const {
  return entities.size();
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

void
EntityManager::tagEntity(Entity *entity, string const &tag) {
  if (!entity->hasTag(tag)) {
    tags[tag].push_back(entity);
    entity->addTag(tag);
  }
}

void
EntityManager::untagEntity(Entity *entity, string const &tag) {
  if (entity->hasTag(tag)) {
    entity->removeTag(tag);
    vector<Entity *> *etags = &tags[tag];
    for (vector<Entity *>::iterator it = etags->begin(); it < etags->end(); it++) {
      if (entity == *it) {
        etags->erase(it);
        return;
      }
    }
  }
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
EntityManager::getEntities() const {
  vector<Entity *> ret;
  for (unsigned int i = 1; i < entities.size(); ++i) {
    Entity *ent = entities[i];
    if (ent != NULL) {
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

vector<Entity *> const &
EntityManager::getByTag(string const &tag) {
  return tags[tag];
}

Entity *
EntityManager::getFirstByTag(string const &tag) {
  vector<Entity *> const &allByTag = getByTag(tag);
  return allByTag.empty() ? NULL : allByTag[0];
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
