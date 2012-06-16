#pragma once
#include "Entity.h"

class EntityManager {
private:
  string name;
  vector<Entity *> entities;

public:
  EntityManager(string const &name);
  ~EntityManager();

  Entity *createEntity();
  Entity *getEntity(Entity::Id id);
  void destroyEntity(Entity::Id id);
  void destroyEntity(Entity *entity);
  vector<Entity *>getEntities(Component::Type t);
  vector<Entity *>getEntities(Component::Type t1, Component::Type t2);
  Entity *getEntity(Component::Type t);

  template<class T> T *getComponent();
  
  string toString() const;
};

template<class T>
T *EntityManager::getComponent() {
  Entity *entity = getEntity(T::TYPE);
  Component *comp = entity->getComponent(T::TYPE);
  return (T *)comp;
}

