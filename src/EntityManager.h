#pragma once

#include <map>
#include "Entity.h"

class EntityManager {
private:
  string name;
  vector<Entity *> entities;
  map<string, vector<Entity *> > tags;

public:
  EntityManager(string const &name);
  ~EntityManager();

  string getName() const;
  int getSize() const;
  
  Entity *createEntity();
  Entity *getEntity(Entity::Id id);
  void destroyEntity(Entity::Id id);
  void destroyEntity(Entity *entity);
  
  void tagEntity(Entity *entity, string const &tag);
  void untagEntity(Entity *entity, string const &tag);

  vector<Entity *> getEntities() const;
  vector<Entity *> getEntities(Component::Type t);
  vector<Entity *> getEntities(Component::Type t1, Component::Type t2);
  Entity *getEntity(Component::Type t);

  vector<Entity *> const &getByTag(const string &tag);
  Entity *getFirstByTag(const string &tag);

  template<class T> T *getComponent();
  
  string toString() const;
};

template<class T>
T *EntityManager::getComponent() {
  Entity *entity = getEntity(T::TYPE);
  Component *comp = entity->getComponent(T::TYPE);
  return (T *)comp;
}

