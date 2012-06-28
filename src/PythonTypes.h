#pragma once

class EntityManager;
class WrappedEntity;
class Component;

void initcp(EntityManager *em);
PyObject *wrapEntityManager(EntityManager *em);
PyObject *wrapEntity(WrappedEntity  *e);
PyObject *wrapComponent(Component *c);
