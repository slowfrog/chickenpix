#include <sstream>
#include "TagEntityManager.h"
#include "EntityManager.h"

EntityManager::EntityManager(string const &name):
  _name(name), _entities(1) {
}

EntityManager::~EntityManager() {
  _entities.clear();
}

string
EntityManager::getName() const {
  return _name;
}

int
EntityManager::getSize() const {
  return _entities.size();
}

Entity *
EntityManager::createEntity() {
  unsigned int i;
  Entity *ent;
  for (i = 1; i < _entities.size(); ++i) {
    ent = _entities[i];
    if (ent == NULL) {
      ent = new Entity(i);
      _entities[i] = ent;
      return ent;
    }
  }
  ent = new Entity(i);
  _entities.push_back(ent);
  return ent;
}

Entity *
EntityManager::getEntity(Entity::Id id) {
  if ((id > 0) && (id < _entities.size())) {
    return _entities[id];
  }
  throw string("No such entity to get");
}

void
EntityManager::destroyEntity(Entity::Id id) {
  if ((id > 0) && (id < _entities.size())) {
    delete _entities[id];
    _entities[id] = NULL;
  } else {
    throw string("No such entity to destroy");
  }
}

void
EntityManager::destroyEntity(Entity *entity) {
  destroyEntity(entity->getId());
}

void
EntityManager::replaceEntity(Entity::Id id, Entity *replacement) {
  // Could add some asserts to check the replacement is valid (good id, same tags). At least in debug.
  delete _entities[id];
  _entities[id] = replacement;
}

vector<Entity *>
EntityManager::getEntities(Component::Type t) {
  vector<Entity *> ret;
  for (unsigned int i = 1; i < _entities.size(); ++i) {
    Entity *ent = _entities[i];
    if ((ent != NULL) && (ent->hasComponent(t))) {
      ret.push_back(ent);
    }
  }
  return ret;
}

vector<Entity *>
EntityManager::getEntities() const {
  vector<Entity *> ret;
  for (unsigned int i = 1; i < _entities.size(); ++i) {
    Entity *ent = _entities[i];
    if (ent != NULL) {
      ret.push_back(ent);
    }
  }
  return ret;
}

vector<Entity *>
EntityManager::getEntities(Component::Type t1, Component::Type t2) {
  vector<Entity *> ret;
  for (unsigned int i = 1; i < _entities.size(); ++i) {
    Entity *ent = _entities[i];
    if ((ent != NULL) && (ent->hasComponents(t1, t2))) {
      ret.push_back(ent);
    }
  }
  return ret;
}

Entity *
EntityManager::getEntity(Component::Type t) {
  for (unsigned int i = 1; i < _entities.size(); ++i) {
    Entity *ent = _entities[i];
    if ((ent != NULL) && (ent->hasComponent(t))) {
      return ent;
    }
  }
  return NULL;
}

void
EntityManager::tagEntity(Entity *entity, string const &tag, const bool unique) {
  CTagEntityMng::get()->registerTag( entity->getId(), tag, unique);
  /*
  if (!entity->hasTag(tag)) {
    _tags[tag].push_back(entity->getId());
    entity->addTag(tag);
  }
   */
}

void
EntityManager::untagEntity(Entity *entity, string const &tag) {
  CTagEntityMng::get()->unregisterTagForEntity( entity->getId(), tag);
  /*
  if (entity->hasTag(tag)) {
    entity->removeTag(tag);
    vector<Entity::Id> *etags = &_tags[tag];
    for (vector<Entity::Id>::iterator it = etags->begin(); it < etags->end(); it++) {
      if (entity->getId() == *it) {
        etags->erase(it);
        return;
      }
    }
  }*/
}

vector<Entity::Id> const &
EntityManager::getByTag(string const &tag) {
  return CTagEntityMng::get()->getEntitiesByTag( tag);
  //return _tags[tag];
}

Entity::Id
EntityManager::getFirstByTag(string const &tag) {
  // Search first in the map of unique tag, 
  // if not found look in the other map 
  Entity::Id l_id = CTagEntityMng::get()->getEntityByTag( tag);
  if ( l_id >= 0){
    return l_id;
  }
  else {
    return CTagEntityMng::get()->getFirstEntityByTag( tag);
  }
  /*
  vector<Entity::Id> const &allByTag = getByTag(tag);
  return allByTag.empty() ? NULL : allByTag[0];
   */
}

string
EntityManager::toString() const {
  ostringstream out;
  out << "{EntityManager name=" << _name << ", entities[";
  int alive = 0;
  int dead = 0;
  for (unsigned int i = 1; i < _entities.size(); ++i) {
    if (_entities[i] != NULL) {
      ++alive;
    } else {
      ++dead;
    }
  }
  out << "alive: " << alive << ", dead:" << dead;
  out << "] tags[ ";
  for (map<string, vector<Entity::Id> >::const_iterator it = _tags.begin();
       it != _tags.end(); it++) {
    out << it->first << " ";
  }
  out << "]}" << ends;
  return out.str();
}
