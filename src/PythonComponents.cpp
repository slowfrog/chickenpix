#include <Python.h>
#include "log.h"
#include "PythonComponents.h"
#include "Camera.h"
#include "Mobile.h"
#include "Transform.h"

static PyObject *NO_ARGS = PyTuple_New(0);
static PyObject *NO_KWDS = PyDict_New();

// Transform wrapper
typedef PyComponent PyTransform;
typedef PyComponent PyMobile;
typedef PyComponent PyCamera;

// Transform type and methods
static PyTypeObject PyTransformType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Transform",
  sizeof(PyTransform),
};

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
  { (char *) "x", Transform_getx, Transform_setx, (char *) "The x coordinate", NULL },
  { (char *) "y", Transform_gety, Transform_sety, (char *) "The y coordinate", NULL },
  { NULL, NULL }
};

static
PyObject *Transform_moveTo(PyTransform *self, PyObject *args) {
  Transform *t = (Transform *) self->component;
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
  } else {
    t->moveTo(x, y);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static
PyObject *Transform_moveBy(PyTransform *self, PyObject *args) {
  Transform *t = (Transform *) self->component;
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
  } else {
    t->moveBy(x, y);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef Transform_methods[] = {
  {"moveTo", (PyCFunction) Transform_moveTo, METH_VARARGS, "Move to a defined position"},
  {"moveBy", (PyCFunction) Transform_moveBy, METH_VARARGS, "Move by a defined displacement"},
  {NULL} /* End of list */
};

// Mobile type and methods -------------------------------------------------------------------
static PyTypeObject PyMobileType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Mobile",
  sizeof(PyMobile),
};

static
int Mobile_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  float speedX, speedY;
  if (!PyArg_ParseTuple(args, "ff", &speedX, &speedY)) {
    return -1;
  }
  self->component = new Mobile(speedX, speedY);
  return 0;
}

static
PyObject *Mobile_getSpeedX(PyObject *self, void *) {
  return PyFloat_FromDouble(((Mobile *) ((PyMobile *) self)->component)->getSpeedX());
}

static
int Mobile_setSpeedX(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speedX must be a number");
    return -1;
  }
  ((Mobile *) ((PyMobile *) self)->component)->setSpeedX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Mobile_getSpeedY(PyObject *self, void *) {
  return PyFloat_FromDouble(((Mobile *) ((PyMobile *) self)->component)->getSpeedY());
}

static
int Mobile_setSpeedY(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speedY must be a number");
    return -1;
  }
  ((Mobile *) ((PyMobile *) self)->component)->setSpeedY((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Mobile_getSpeed(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
  return PyTuple_Pack(2, PyFloat_FromDouble(m->getSpeedX()), PyFloat_FromDouble(m->getSpeedY()));
}

static
int Mobile_setSpeed(PyObject *self, PyObject *val, void *) {
  if (!PyTuple_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speed must be a tuple");
    return -1;
  }
  if (PyTuple_Size(val) != 2) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speed must be a two-value tuple");
    return -1;
  }
  PyObject *psx = PyTuple_GetItem(val, 0);
  PyObject *psy = PyTuple_GetItem(val, 1);
  if (!PyNumber_Check(psx)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speed must be a tuple with numbers (first element is not)");
    return -1;
  }
  if (!PyNumber_Check(psy)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speed must be a tuple with numbers (second element is not)");
    return -1;
  }
  
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
  float sx = (float) PyFloat_AsDouble(psx);
  float sy = (float) PyFloat_AsDouble(psy);
  m->setSpeed(sx, sy);
  return 0;
}

static PyGetSetDef Mobile_getset[] = {
  { (char *) "speedX", Mobile_getSpeedX, Mobile_setSpeedX, (char *) "The x speed", NULL },
  { (char *) "speedY", Mobile_getSpeedY, Mobile_setSpeedY, (char *) "The y speed", NULL },
  { (char *) "speed", Mobile_getSpeed, Mobile_setSpeed, (char *) "The speed as a tuple of two numbers", NULL },
  { NULL, NULL }
};

// Camera type and methods -------------------------------------------------------------------
static PyTypeObject PyCameraType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Camera",
  sizeof(PyCamera),
};

static
int Camera_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  float offsetX, offsetY;
  if (!PyArg_ParseTuple(args, "ff", &offsetX, &offsetY)) {
    return -1;
  }
  self->component = new Camera(offsetX, offsetY);
  return 0;
}

static
PyObject *Camera_getOffsetX(PyObject *self, void *) {
  return PyFloat_FromDouble(((Camera *) ((PyCamera *) self)->component)->getOffsetX());
}

static
int Camera_setOffsetX(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.offsetX must be a number");
    return -1;
  }
  ((Camera *) ((PyCamera *) self)->component)->setOffsetX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Camera_getOffsetY(PyObject *self, void *) {
  return PyFloat_FromDouble(((Camera *) ((PyCamera *) self)->component)->getOffsetY());
}

static
int Camera_setOffsetY(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.offsetY must be a number");
    return -1;
  }
  ((Camera *) ((PyCamera *) self)->component)->setOffsetY((float) PyFloat_AsDouble(val));
  return 0;
}

static PyGetSetDef Camera_getset[] = {
  { (char *) "offsetX", Camera_getOffsetX, Camera_setOffsetX, (char *) "The x offset", NULL },
  { (char *) "offsetY", Camera_getOffsetY, Camera_setOffsetY, (char *) "The y offset", NULL },
  { NULL, NULL }
};

// Real initialization -----------------------------------------------------------------------
void
initComponents(PyObject *module) {
  PyObject *type;
  
  // Transform
  PyTransformType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyTransformType.tp_doc = "Type of transform components";
  PyTransformType.tp_methods = Transform_methods;
  PyTransformType.tp_base = &PyComponentType;
  PyTransformType.tp_init = (initproc) Transform_init;
  PyTransformType.tp_getset = Transform_getset;
  if (PyType_Ready(&PyTransformType) < 0) {
    LOG2 << "Cannot create Transform type\n";
    return;
  }
  Py_INCREF(&PyTransformType);
  PyModule_AddObject(module, "Transform", (PyObject *) &PyTransformType);
  type = PyInt_FromLong(Transform::TYPE);
  PyDict_SetItemString(PyTransformType.tp_dict, "TYPE", type);
  Py_DECREF(type);

  // Mobile
  PyMobileType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyMobileType.tp_doc = "Type of mobile components";
  //PyMobileType.tp_methods = XXX
  PyMobileType.tp_base = &PyComponentType;
  PyMobileType.tp_init = (initproc) Mobile_init;
  PyMobileType.tp_getset = Mobile_getset;
  if (PyType_Ready(&PyMobileType) < 0) {
    LOG2 << "Cannot create Mobile type\n";
    return;
  }
  Py_INCREF(&PyMobileType);
  PyModule_AddObject(module, "Mobile", (PyObject *) &PyMobileType);
  type = PyInt_FromLong(Mobile::TYPE);
  PyDict_SetItemString(PyMobileType.tp_dict, "TYPE", type);
  Py_DECREF(type);
  
  // Camera
  PyCameraType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyCameraType.tp_doc = "Type of camera components";
  //PyCameraType.tp_methods = XXX
  PyCameraType.tp_base = &PyComponentType;
  PyCameraType.tp_init = (initproc) Camera_init;
  PyCameraType.tp_getset = Camera_getset;
  if (PyType_Ready(&PyCameraType) < 0) {
    LOG2 << "Cannot create Camera type\n";
    return;
  }
  Py_INCREF(&PyCameraType);
  PyModule_AddObject(module, "Camera", (PyObject *) &PyCameraType);
  type = PyInt_FromLong(Camera::TYPE);
  PyDict_SetItemString(PyCameraType.tp_dict, "TYPE", type);
  Py_DECREF(type);
}

PyObject *
wrapTransform(Transform *t) {
  PyTransform *pyt = (PyTransform *) PyTransformType.tp_alloc(&PyTransformType, 0);
  pyt->component = t;
  return (PyObject *) pyt;
}

PyObject *
wrapMobile(Mobile *c) {
  PyMobile *pyc = (PyMobile *) PyMobileType.tp_alloc(&PyMobileType, 0);
  pyc->component = c;
  return (PyObject *) pyc;
}

PyObject *
wrapCamera(Camera *c) {
  PyCamera *pyc = (PyCamera *) PyCameraType.tp_alloc(&PyCameraType, 0);
  pyc->component = c;
  return (PyObject *) pyc;
}


PyObject *
wrapRealComponent(Component *c) {
  switch (c->getType()) {
  case Transform::TYPE:
    return wrapTransform((Transform *) c);
  case Mobile::TYPE:
    return wrapMobile((Mobile *) c);
  case Camera::TYPE:
    return wrapCamera((Camera *) c);
  default:
    return NULL;
  }
}
