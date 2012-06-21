#include <Python.h>

#include "PythonTypes.h"

// EntityManager wrapper
typedef struct {
  PyObject_HEAD
  EntityManager *em;
} PyEntityManager;

static PyTypeObject PyEntityManagerType = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "cp.EntityManager",        /*tp_name*/
  sizeof(PyEntityManager), /*tp_basicsize*/
};



static PyObject *
EntityManager_name(PyEntityManager *self) {
  PyObject *ret = PyString_FromString(self->em->getName().c_str());
  return ret;
}

// Entity wrapper
typedef struct {
  PyObject_HEAD
  Entity *entity;
} PyEntity;

static PyTypeObject PyEntityType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Entity",
  sizeof(PyEntity),
};



static PyMethodDef module_Methods[] = {
  {NULL} /* End of list */
};

static PyMethodDef EntityManager_methods[] = {
  {"name", (PyCFunction)EntityManager_name, METH_NOARGS, "Name of the EntityManager" },
  {NULL} /* End of list */
};

void
initcp(EntityManager *em) {
  PyObject* m;
  
  PyEntityManagerType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyEntityManagerType.tp_doc = "Type of entity managers";
  PyEntityManagerType.tp_new = PyType_GenericNew;
  PyEntityManagerType.tp_methods = EntityManager_methods;
  if (PyType_Ready(&PyEntityManagerType) < 0)
    return;

  PyEntityType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyEntityType.tp_doc = "Type of entities";
  PyEntityType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyEntityType) < 0)
    return;

  m = Py_InitModule3("cp", module_Methods,
                     "Chickenpix extension module.");
  
  Py_INCREF(&PyEntityManagerType);
  PyModule_AddObject(m, "EntityManager", (PyObject *) &PyEntityManagerType);
  Py_INCREF(&PyEntityType);
  PyModule_AddObject(m, "Entity", (PyObject *) &PyEntityType);

  PyEntityManager *pyem = (PyEntityManager *) PyEntityManagerType.tp_alloc(&PyEntityManagerType, 0);
  pyem->em = em;
  PyModule_AddObject(m, "em", (PyObject *) pyem);
}

PyObject *wrapEntityManager(EntityManager *em) {
  PyEntityManager *pyem = (PyEntityManager *) PyEntityManagerType.tp_alloc(&PyEntityManagerType, 0);
  pyem->em = em;
  return (PyObject *) pyem;
}
