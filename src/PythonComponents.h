#pragma once

#include "Types.h"

class EntityManager;

void initComponents(PyObject *module);
PyObject *wrapRealComponent(Component *c);
