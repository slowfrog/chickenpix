#pragma once

#include "PythonTypes.h"

class Transform;

// Transform wrapper
typedef PyComponent PyTransform;


void initComponents(PyObject *module);
PyObject *wrapRealComponent(Component *c);
