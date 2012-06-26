#pragma once
#include <string>
#include <vector>
#include "Component.h"

using namespace std;

class Entity {
  friend class EntityManager;
  
public:
  typedef unsigned int Id;
  
private:
  static const Id INVALID_ID = 0;
  
  Id id;
  vector<Component *> comp;
  vector<string> tags;
  
public:

  Entity();
  
  explicit Entity(Id id);
  
  ~Entity();

  inline Id getId() const {
    return id;
  }

  inline vector<Component *> const &getComponents() const {
    return comp;
  }
  
  void addComponent(Component *c);
  void removeComponent(Component::Type t);
  Component *getComponent(Component::Type t);
  template<class T>  T *getComponent();
  bool hasComponent(Component::Type t) const;
  bool hasComponents(Component::Type t1, Component::Type t2) const;

  bool hasTag(string const &tag) const;
  inline
  vector<string> const &getTags() const {
    return tags;
  }

  string toString() const;

protected:
  void addTag(string const &tag);
  void removeTag(string const &tag);
};

template<class T>
T *Entity::getComponent() {
  return (T *)getComponent(T::TYPE);
}
