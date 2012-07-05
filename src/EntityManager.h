#pragma once

#include <map>
#include "Types.h"
#include "Entity.h"

/**
 * An EntityManager manages entities (obviously). This means that Entity objects
 * should only be created by a manager (calling createEntity) and should only be
 * deleted by calling destroyEntity().
 * Also tagging and un-tagging entities should be done through the manager,
 * because it keeps track of groups of entities by tag.
 */
class EntityManager {
public:
private:
  /** Name of the manager. Mostly useless. */
  string _name;
  /** Currently owned entities. Some entries might be NULL. */
  vector<Entity *> _entities;
  /** Entities grouped by tags. */
  map<string, vector<Entity::Id> > _tags;

public:
  EntityManager(string const &name);
  ~EntityManager();

  string getName() const;
  int getSize() const;
  
  Entity *createEntity();
  Entity *getEntity(Entity::Id id);
  void destroyEntity(Entity::Id id);
  void destroyEntity(Entity *entity);
  
  /**
   * When you need to store entities of a more specific type, you should call replaceEntity to notify
   * the manager that it has changed. The caller is responsible for copying all the contents of the
   * entity that is replaced. Don't keep a reference to the previous entity: the manager will destroy
   * it in this function.
   */
  void replaceEntity(Entity::Id id, Entity *replacement);

  TEntityList getEntities() const;
  TEntityList  getEntities(Component::Type t);
  TEntityList  getEntities(Component::Type t1, Component::Type t2);
  Entity *getEntity(Component::Type t);

  /**
   * Tags management
   */
  void tagEntity(Entity *entity, string const &tag, const bool unique=false);
  void untagEntity(Entity *entity, string const &tag);
  vector<Entity::Id> const &getByTag(const string &tag);
  Entity::Id getFirstByTag(const string &tag);

  template<class T> T *getComponent();
  
  string toString() const;
};

template<class T>
T *EntityManager::getComponent() {
  Entity *entity = getEntity(T::TYPE);
  Component *comp = entity->getComponent(T::TYPE);
  return (T *)comp;
}

