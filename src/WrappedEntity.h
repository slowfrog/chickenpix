#pragma once
#include <Python.h>
#include "Entity.h"
#include "PythonTypes.h"

class WrappedEntity: public Entity {
private:
  PyObject *_wrapper;
  PyObject *_dict;
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

  // Free dictionary of values used by scripts
  PyObject *getDict() const;
  PyObject *getOrCreateDict();
  int setItem(PyObject *key, PyObject *val);
  int delItem(PyObject *key);
  int contains(PyObject *key);
  PyObject *getItem(PyObject *key);
};
