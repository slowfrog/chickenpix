#include <Python.h>

#include <iostream>
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

static PyObject *
EntityManager_size(PyEntityManager *self) {
  PyObject *ret = PyInt_FromLong(self->em->getSize());
  return ret;
}

static PyObject *


EntityManager_getEntities(PyEntityManager *self) {
  EntityManager *em = self->em;
  vector<Entity *> const &entities = em->getEntities();
  int size = entities.size();
  PyObject *ret = PyList_New(size);
  for (int i = 0; i < size; ++i) {
    Entity *entity = entities[i];
    PyObject *pentity = wrapEntity(entity);
    PyList_SetItem(ret, i, pentity);
  }
  return ret;
}

static PyMethodDef EntityManager_methods[] = {
  {"name", (PyCFunction) EntityManager_name, METH_NOARGS, "Name of the EntityManager" },
  {"size", (PyCFunction) EntityManager_size, METH_NOARGS, "Number of entities" },
  {"getEntities", (PyCFunction) EntityManager_getEntities, METH_NOARGS, "List of all entities" },
  {NULL} /* End of list */
};

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

static PyObject *
Entity_id(PyEntity *self) {
  PyObject *ret = PyInt_FromLong(self->entity->getId());
  return ret;
};

static PyMethodDef Entity_methods[] = {
  {"id", (PyCFunction) Entity_id, METH_NOARGS, "Id of the entity" },
  {NULL} /* End of list */
};

//////
static PyMethodDef module_Methods[] = {
  {NULL} /* End of list */
};



void
initcp(EntityManager *em) {
  PyObject* m;
  
  PyEntityManagerType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyEntityManagerType.tp_doc = "Type of entity managers";
  PyEntityManagerType.tp_new = PyType_GenericNew; // Remove ?
  PyEntityManagerType.tp_methods = EntityManager_methods;
  if (PyType_Ready(&PyEntityManagerType) < 0)
    return;

  PyEntityType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyEntityType.tp_doc = "Type of entities";
  PyEntityType.tp_new = PyType_GenericNew; // Remove ?
  PyEntityType.tp_methods = Entity_methods;
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

PyObject *wrapEntity(Entity *e) {
  PyEntity *pye = (PyEntity *) PyEntityType.tp_alloc(&PyEntityType, 0);
  pye->entity = e;
  return (PyObject *) pye;
}
