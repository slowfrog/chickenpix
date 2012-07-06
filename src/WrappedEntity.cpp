#include <Python.h> // Always include Python before standard includes
#include <iostream>
#include "WrappedEntity.h"
#include "EntityManager.h"
#include "Component.h"

const Entity::Type WrappedEntity::TYPE = 2;

WrappedEntity *
WrappedEntity::wrap(EntityManager &em, Entity *entity) {
  if (isInstance(entity)) {
    return (WrappedEntity *) entity;
  } else {
    WrappedEntity *ret = new WrappedEntity(*entity);
    em.replaceEntity(entity->getId(), ret);
    return ret;
  }
}

WrappedEntity::WrappedEntity(Entity &src):
  Entity(src, TYPE), _wrapper(NULL), _dict(NULL) {
  
  _wrapper = wrapEntity(this);
  src.releaseComponents(); // If we don't release them, they will be destroyed
                           // when the source entity is deleted
}

WrappedEntity::~WrappedEntity() {
  Py_XDECREF(_dict); // Maybe we must also free all the contents...
  Py_DECREF(_wrapper);
}

PyObject *
WrappedEntity::getWrapper() const {
  return _wrapper;
}

PyObject *
WrappedEntity::getDict() const {
  return _dict;
}

PyObject *
WrappedEntity::getOrCreateDict() {
  if (_dict == NULL) {
    _dict = PyDict_New();
  }
  return _dict;
}

int
WrappedEntity::setItem(PyObject *key, PyObject *val) {
  int ret = PyDict_SetItem(getOrCreateDict(), key, val);
  return ret;
}

int
WrappedEntity::delItem(PyObject *key) {
  return PyDict_DelItem(getOrCreateDict(), key);
}

int
WrappedEntity::contains(PyObject *key) {
  return PyDict_Contains(getOrCreateDict(), key);
}

PyObject *
WrappedEntity::getItem(PyObject *key) {
  PyObject *ret = PyDict_GetItem(getOrCreateDict(), key);
  if (ret == NULL) {
    PyErr_SetObject(PyExc_AttributeError, key);
    return NULL;
  } else {
    Py_INCREF(ret);
    return ret;
  }
}

