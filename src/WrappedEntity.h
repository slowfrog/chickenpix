#pragma once
#include <Python.h>
#include "Entity.h"
#include "PythonTypes.h"

class WrappedEntity: public Entity {
private:
  PyObject *wrapper;
public:
  static const Type TYPE; // = 2
  
  WrappedEntity(Entity &src);
  virtual ~WrappedEntity();

  static WrappedEntity *wrap(EntityManager &em, Entity *entity);
  
  inline
  static bool isInstance(Entity *entity) {
    return entity->getType() == TYPE;
  }
  
  PyObject *getWrapper() const;
};
