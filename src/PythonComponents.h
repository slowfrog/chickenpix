#pragma once

#include "PythonTypes.h"

void initComponents(PyObject *module);
PyObject *wrapRealComponent(Component *c);
