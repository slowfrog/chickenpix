#include <sstream>
#include "TagEntityManager.h"
#include "Stats.h"
#include "EntityManager.h"

string
EntityManager::EXIT = "EXIT";

EntityManager::EntityManager(string const &name):
  name_(name), entities_(1), nameRequired_(name) {
}

EntityManager::~EntityManager() {
  entities_.clear();
}

string
EntityManager::getName() const {
  return name_;
}

int
EntityManager::getSize() const {
  return entities_.size();
}

// Gestion temporaire du switch
void 
EntityManager::setSwitch(const string &name){
  nameRequired_ = name;
}

bool 
EntityManager::switchRequired() const {
  return (nameRequired_ != name_);
}

bool
EntityManager::exitRequested() const {
  return nameRequired_ == EXIT;
}

// </>

Entity *
EntityManager::createEntity() {
  unsigned int i;
  Entity *ent;
  for (i = 1; i < entities_.size(); ++i) {
    ent = entities_[i];
    if (ent == NULL) {
      ent = new Entity(i);
      entities_[i] = ent;
      return ent;
    }
  }
  ent = new Entity(i);
  entities_.push_back(ent);
  return ent;
}

Entity *
EntityManager::getById(Entity::Id id) {
  if ( id >= 1) {
    for( std::size_t i = 1; i<entities_.size(); i++){
      if ( entities_[i] && id == entities_[i]->getId()) {
        return entities_[i];
      }
    }
  }
  return NULL;
}

void
EntityManager::destroyEntity(Entity::Id id) {
  if ((id > 0) && (id < entities_.size())) {
    delete entities_[id];
    entities_[id] = NULL;
  } else {
    throw string("No such entity to destroy");
  }
}

void
EntityManager::destroyEntity(Entity *entity) {
  destroyEntity(entity->getId());
}

void 
EntityManager::destroyEntitiesByTag( const std::string &tag){
  CTagEntityMng::TVId lent = getTagMng().getEntitiesByTag( tag);
  for ( std::size_t ind =0; ind< lent.size(); ind++) {
    destroyEntity( lent[ind]);
    getTagMng().unregisterTagForEntity( lent[ind], tag);
  }
}

void
EntityManager::replaceEntity(Entity::Id id, Entity *replacement) {
  // Could add some asserts to check the replacement is valid (good id, same tags). At least in debug.
  delete entities_[id];
  entities_[id] = replacement;
}

TEntityList
EntityManager::getEntities(Component::Type t) {
  TEntityList ret;
  for (unsigned int i = 1; i < entities_.size(); ++i) {
    Entity *ent = entities_[i];
    if ((ent != NULL) && (ent->hasComponent(t))) {
      ret.push_back(ent);
    }
  }
  return ret;
}

TEntityList
EntityManager::getEntities() const {
  TEntityList ret;
  for (unsigned int i = 1; i < entities_.size(); ++i) {
    Entity *ent = entities_[i];
    if (ent != NULL) {
      ret.push_back(ent);
    }
  }
  return ret;
}

TEntityList
EntityManager::getEntities(Component::Type t1, Component::Type t2) {
  TEntityList ret;
  for (unsigned int i = 1; i < entities_.size(); ++i) {
    Entity *ent = entities_[i];
    if ((ent != NULL) && (ent->hasComponents(t1, t2))) {
      ret.push_back(ent);
    }
  }
  return ret;
}

Entity *
EntityManager::getFirst(Component::Type t) {
  for (unsigned int i = 1; i < entities_.size(); ++i) {
    Entity *ent = entities_[i];
    if ((ent != NULL) && (ent->hasComponent(t))) {
      return ent;
    }
  }
  return NULL;
}

void EntityManager::addEntity( Entity *e){
  assert(e);
  if ( !getById( e->getId())) {
    entities_.push_back( e);
  }
}

void
EntityManager::tagEntity(Entity *entity, string const &tag, const bool unique) {
  mTagMng.registerTag( entity->getId(), tag, unique);
  /*
  if (!entity->hasTag(tag)) {
    _tags[tag].push_back(entity->getId());
    entity->addTag(tag);
  }
   */
}

void
EntityManager::untagEntity(Entity *entity, string const &tag) {
  mTagMng.unregisterTagForEntity( entity->getId(), tag);
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

vector<Entity::Id> const
EntityManager::getByTag(string const &tag) {
  return mTagMng.getEntitiesByTag( tag);
  //return _tags[tag];
}

Entity::Id
EntityManager::getFirstByTag(string const &tag) {
  // Search first in the map of unique tag, 
  // if not found look in the other map 
  return mTagMng.getFirstEntityByTag( tag);
  
  /*
  Entity::Id l_id = mTagMng.getEntityByTag( tag);
  if ( l_id != NOT_FOUND){
    return l_id;
  }
  else {
    return mTagMng.getFirstEntityByTag( tag);
  }
  /*
  vector<Entity::Id> const &allByTag = getByTag(tag);
  return allByTag.empty() ? NULL : allByTag[0];
   */
}

string
EntityManager::toString() const {
  ostringstream out;
  out << "{EntityManager name=" << name_ << ", entities[";
  int alive = 0;
  int dead = 0;
  for (unsigned int i = 1; i < entities_.size(); ++i) {
    if (entities_[i] != NULL) {
      ++alive;
    } else {
      ++dead;
    }
  }
  out << "alive: " << alive << ", dead:" << dead;
  out << "] tags[ ";
  for (map<string, vector<Entity::Id> >::const_iterator it = tags_.begin();
       it != tags_.end(); it++) {
    out << it->first << " ";
  }
  out << "]}" << ends;
  return out.str();
}
