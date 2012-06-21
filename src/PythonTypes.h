#pragma once

#include "EntityManager.h"

void initcp(EntityManager *em);
PyObject *wrapEntityManager(EntityManager *em);
PyObject *wrapEntity(Entity  *em);
