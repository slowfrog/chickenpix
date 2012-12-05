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
 
#pragma once

#include <map>
#include <cassert>
#include "Types.h"
#include "Entity.h"
#include "TagEntityManager.h"

// Constants
#define MENU  "Menu"
#define MAIN  "Main"
#define FIGHT "Fight"

/**
 * An EntityManager manages entities (obviously). This means that Entity objects
 * should only be created by a manager (calling createEntity) and should only be
 * deleted by calling destroyEntity().
 * Also tagging and un-tagging entities should be done through the manager,
 * because it keeps track of groups of entities by tag.
 */
class EntityManager {
public:
  static string EXIT;
  CTagEntityMng mTagMng;
  inline CTagEntityMng& getTagMng() { return mTagMng;}
  
private:
  /** Name of the manager. Mostly useless. */
  string name_;
  /** Currently owned entities. Some entries might be NULL. */
  vector<Entity *> entities_;
  /** Entities grouped by tags. */
  map<string, vector<Entity::Id> > tags_;
  /** Switch needed */
  std::string nameRequired_;

public:
  EntityManager(string const &name);
  ~EntityManager();

  string getName() const;
  int getSize() const;
  
  void setSwitch(const string&);
  bool switchRequired() const;
  bool exitRequested() const;
  inline const string& requiredName() const { return nameRequired_; }
  
  Entity *createEntity();
  Entity *getById(Entity::Id id);
  void addEntity    ( Entity*);
  void destroyEntity(Entity::Id id);
  void destroyEntity(Entity *entity);
  
  /**
   * When you need to store entities of a more specific type, you should call
   * replaceEntity to notify the manager that it has changed. The caller is
   * responsible for copying all the contents of the entity that is replaced.
   * Don't keep a reference to the previous entity: the manager will destroy
   * it in this function.
   */
  void replaceEntity(Entity::Id id, Entity *replacement);

  TEntityList getEntities() const;
  TEntityList getEntities(Component::Type t);
  TEntityList getEntities(Component::Type t1, Component::Type t2);
  Entity      *getFirst (Component::Type t);

  /**
   * Tags management
   */
  void tagEntity(Entity *entity, string const &tag, const bool unique=false);
  void untagEntity(Entity *entity, string const &tag);
  vector<Entity::Id> const getByTag(const string &tag);
  Entity::Id getFirstByTag(const string &tag);
  void destroyEntitiesByTag( const string&);

  /**
   * Components access
   */
  template<class T> T *getComponent();
  
  // Debug
  string toString() const;
};

template<class T>
T *EntityManager::getComponent() {
  Entity *entity = getFirst(T::TYPE);
  assert( entity);
  Component *comp = entity->getComponent(T::TYPE);
  return (T *)comp;
}

