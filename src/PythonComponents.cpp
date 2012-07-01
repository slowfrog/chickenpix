#include <Python.h>
#include "log.h"
#include "PythonComponents.h"
#include "Transform.h"

using namespace std;

// Transform type and methods
static PyTypeObject PyTransformType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Transform",
  sizeof(PyTransform),
};

static PyObject *NO_ARGS = PyTuple_New(0);
static PyObject *NO_KWDS = PyDict_New();

static
int Transform_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    return -1;
  }
  self->component = new Transform(x, y);
  return 0;
}

static
PyObject *Transform_getx(PyObject *self, void *) {
  return PyFloat_FromDouble(((Transform *) ((PyTransform *) self)->component)->getX());
}

static
int Transform_setx(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Transform.x must be a number");
    return -1;
  }
  ((Transform *) ((PyTransform *) self)->component)->setX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Transform_gety(PyObject *self, void *) {
  return PyFloat_FromDouble(((Transform *) ((PyTransform *) self)->component)->getY());
}

static
int Transform_sety(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Transform.y must be a number");
    return -1;
  }
  ((Transform *) ((PyTransform *) self)->component)->setY((float) PyFloat_AsDouble(val));
  return 0;
}

static PyGetSetDef Transform_getset[] = {
  { "x", Transform_getx, Transform_setx, "The x coordinate", NULL },
  { "y", Transform_gety, Transform_sety, "The y coordinate", NULL },
  { NULL, NULL }
};

void
initComponents(PyObject *module) {
  PyTransformType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyTransformType.tp_doc = "Type of transform components";
  //PyTransformType.tp_methods = XXXX
  PyTransformType.tp_base = &PyComponentType;
  PyTransformType.tp_init = (initproc) Transform_init;
  PyTransformType.tp_getset = Transform_getset;
  if (PyType_Ready(&PyTransformType) < 0) {
    LOG2 << "Cannot create Transform type\n";
    return;
  }
  Py_INCREF(&PyTransformType);
  PyModule_AddObject(module, "Transform", (PyObject *) &PyTransformType);
  PyObject *val = PyInt_FromLong(Transform::TYPE);
  PyDict_SetItemString(PyTransformType.tp_dict, "TYPE", val);
  Py_DECREF(val);
}

PyObject *
wrapTransform(Transform *t) {
  PyTransform *pyt = (PyTransform *) PyTransformType.tp_alloc(&PyTransformType, 0);
  pyt->component = t;
  return (PyObject *) pyt;
}


PyObject *
wrapRealComponent(Component *c) {
  switch (c->getType()) {
  case Transform::TYPE:
    return wrapTransform((Transform *) c);
  default:
    return NULL;
  }
}
