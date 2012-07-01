#pragma once
#include <string>
#include <vector>
#include "Component.h"

using namespace std;

class Entity {
  friend class EntityManager;
  
public:
  typedef unsigned long Id;
  typedef unsigned int  Type;
  
  static const Type TYPE; // = 1
  
private:
  static const Id INVALID_ID = 0;
  
  Id _id;
  Type _type;
  vector<Component *> comp;
  //vector<string> tags;
  
public:

  Entity();
  
  explicit Entity(Id id);
  Entity(Entity const &src);
  
  virtual ~Entity();

  inline Id getId() const {
    return _id;
  }

  inline Type getType() const {
    return _type;
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

  /*bool hasTag(string const &tag) const;
  inline
  vector<string> const &getTags() const {
    return tags;
  }*/

  inline
  static bool isInstance(Entity *entity) {
    return entity->getType() == TYPE;
  }
  
  string toString() const;

  void releaseComponents();
  
protected:
  Entity(Entity const &src, Type type);
  //void addTag(string const &tag);
  //void removeTag(string const &tag);
};

template<class T>
T *Entity::getComponent() {
  return (T *)getComponent(T::TYPE);
}
