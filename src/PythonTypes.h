#pragma once

class EntityManager;
class WrappedEntity;
class Component;

// EntityManager wrapper
typedef struct {
  PyObject_HEAD
  EntityManager *em;
} PyEntityManager;

extern PyTypeObject PyEntityManagerType;


// Entity wrapper
typedef struct {
  PyObject_HEAD
  WrappedEntity *wentity;
} PyEntity;

extern PyTypeObject PyEntityMType;


// Component wrapper
typedef struct {
  PyObject_HEAD
  Component *component;
} PyComponent;

extern PyTypeObject PyComponentType;


// API
void initcp(EntityManager *em);
PyObject *wrapEntityManager(EntityManager *em);
PyObject *wrapEntity(WrappedEntity  *e);
PyObject *wrapComponent(Component *c);
