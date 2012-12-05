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

