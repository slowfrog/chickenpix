#include <Python.h>

#include <iostream>
#include <sstream>
#include "PythonTypes.h"
#include "WrappedEntity.h"
#include "EntityManager.h"
#include "TagEntityManager.h"

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

// Entity wrapper
typedef struct {
  PyObject_HEAD
  WrappedEntity *wentity;
} PyEntity;

static PyTypeObject PyEntityType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Entity",
  sizeof(PyEntity),
};


// EntityManager methods
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
EntityManager_getEntities(PyEntityManager *self, PyObject *args) {
  EntityManager *em = self->em;

  int type1 = 0;
  int type2 = 0;
  if (!PyArg_ParseTuple(args, "|ii", &type1, &type2)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return Py_None;
  }
  vector<Entity *> const &entities =
    (type1 == 0) ? em->getEntities() :
    (type2 == 0) ? em->getEntities(type1) :
    em->getEntities(type1, type2);

  int size = entities.size();
  PyObject *ret = PyList_New(size);
  for (int i = 0; i < size; ++i) {
    Entity *entity = entities[i];
    PyObject *pentity = WrappedEntity::wrap(*em, entity)->getWrapper();
    Py_INCREF(pentity); // Because PyList_SetItem steals the reference
    PyList_SetItem(ret, i, pentity);
  }
  return ret;
}

static PyObject *
EntityManager_tagEntity(PyEntityManager *self, PyObject *args) {
  EntityManager *em = self->em;

  PyEntity *entity;
  const char *tag;
  if (!PyArg_ParseTuple(args, "O!s", &PyEntityType, &entity, &tag)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return Py_None;
  }
  em->tagEntity(entity->wentity, tag);
  return Py_None;
}

static PyObject *
EntityManager_untagEntity(PyEntityManager *self, PyObject *args) {
  EntityManager *em = self->em;

  PyEntity *entity;
  const char *tag;
  if (!PyArg_ParseTuple(args, "O!s", &PyEntityType, &entity, &tag)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return Py_None;
  }
  em->untagEntity(entity->wentity, tag);
  return Py_None;
}

static PyObject *
EntityManager_getByTag(PyEntityManager *self, PyObject *args) {
  EntityManager *em = self->em;

  const char *tag;
  if (!PyArg_ParseTuple(args, "s", &tag)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return Py_None;
  }

  vector<Entity::Id> const &entities = em->getByTag(tag);
  int size = entities.size();
  PyObject *ret = PyList_New(size);
  for (int i = 0; i < size; ++i) {
    WrappedEntity *wentity = WrappedEntity::wrap(*em, em->getEntity(entities[i]));
    PyObject *pentity = wentity->getWrapper();
    Py_INCREF(pentity); // Because PyList_SetItem steals the reference
    PyList_SetItem(ret, i, pentity);
  }
  return ret;
}

static PyMethodDef EntityManager_methods[] = {
  {"name", (PyCFunction) EntityManager_name, METH_NOARGS, "Name of the EntityManager" },
  {"size", (PyCFunction) EntityManager_size, METH_NOARGS, "Number of entities" },
  {"getEntities", (PyCFunction) EntityManager_getEntities, METH_VARARGS, "List of all entities" },
  {"getByTag", (PyCFunction) EntityManager_getByTag, METH_VARARGS, "List entities with the given tag" },
  {"tagEntity", (PyCFunction) EntityManager_tagEntity, METH_VARARGS, "Tag an existing entity" },
  {"untagEntity", (PyCFunction) EntityManager_untagEntity, METH_VARARGS, "Remove tag from existing entity" },
  {NULL} /* End of list */
};

// Entity methods
static PyObject *
Entity_id(PyEntity *self) {
  PyObject *ret = PyInt_FromLong(self->wentity->getId());
  return ret;
}

static PyObject *
Entity_getComponents(PyEntity *self) {
  Entity *entity = self->wentity;
  vector<Component *> const &components = entity->getComponents();
  int size = components.size();
  PyObject *ret = PyList_New(size);
  for (int i = 0; i < size; ++i) {
    Component *compo = components[i];
    PyObject *pcompo = wrapComponent(compo);
    Py_INCREF(pcompo); // Because PyList_SetItem steals the reference
    PyList_SetItem(ret, i, pcompo);
  }
  return ret;
}

static PyObject *
Entity_getTags(PyEntity *self) {
  Entity *entity = self->wentity;
  vector<string> const &tags = CTagEntityMng::get()->getTagsByEntity( entity->getId());/*entity->getTags();*/
  int size = tags.size();
  PyObject *ret = PyList_New(size);
  for (int i = 0; i < size; ++i) {
    string const &tag = tags[i];
    PyObject *ptag = PyString_FromString(tag.c_str());
    Py_INCREF(ptag); // Because PyList_SetItem steals the reference
    PyList_SetItem(ret, i, ptag);
  }
  return ret;
}

static PyObject *
Entity_getDict(PyEntity *self) {
  WrappedEntity *wentity = self->wentity;
  return wentity->getOrCreateDict();
}

static PyMethodDef Entity_methods[] = {
  {"id", (PyCFunction) Entity_id, METH_NOARGS, "Id of the entity" },
  {"getComponents", (PyCFunction) Entity_getComponents, METH_NOARGS, "Get all components of the entity" },
  {"getTags", (PyCFunction) Entity_getTags, METH_NOARGS, "Get all tags on the entity" },
  {"getDict", (PyCFunction) Entity_getDict, METH_NOARGS, "Get the dictionary of values associated to the entity" },
  {NULL} /* End of list */
};

static int
Entity_setAttr(PyObject *self, PyObject *key, PyObject *val) {
  PyObject *method = Py_FindMethod(Entity_methods, self, PyString_AsString(key));
  if (method != NULL) {
    ostringstream out;
    out << "Trying to override method: '" << PyString_AsString(key) << "'" << ends;
    PyErr_SetString(PyExc_RuntimeError, out.str().c_str());
    return -1;
  } else {
    PyErr_Clear();
    WrappedEntity *wentity = ((PyEntity *) self)->wentity;
    int ret = wentity->setItem(key, val);
    return ret;
  }
}

static PyObject *
Entity_getAttr(PyObject *self, PyObject *key) {
  PyObject *method = Py_FindMethod(Entity_methods, self, PyString_AsString(key));
  if (method != NULL) {
    return method;
  } else {
    PyErr_Clear();
    WrappedEntity *wentity = ((PyEntity *) self)->wentity;
    return wentity->getItem(key);
  }
}

// Component wrapper
typedef struct {
  PyObject_HEAD
  Component *component;
} PyComponent;

static PyTypeObject PyComponentType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Component",
  sizeof(PyComponent),
};

static PyObject *
Component_type(PyComponent *self) {
  PyObject *ret = PyInt_FromLong(self->component->getType());
  return ret;
}

static PyObject *
Component_typeName(PyComponent *self) {
  PyObject *ret = PyString_FromString(self->component->getTypeName());
  return ret;
}

static PyMethodDef Component_methods[] = {
  {"type", (PyCFunction) Component_type, METH_NOARGS, "Type of the component" },
  {"typeName", (PyCFunction) Component_typeName, METH_NOARGS, "Name of the type of the component" },
  {NULL} /* End of list */
};

////// Module methods
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
  if (PyType_Ready(&PyEntityManagerType) < 0) {
    cout << "Cannot create EntityManager type" << endl;
    return;
  }

  PyEntityType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyEntityType.tp_doc = "Type of entities";
  PyEntityType.tp_new = PyType_GenericNew; // Remove ?
  PyEntityType.tp_methods = Entity_methods;
  PyEntityType.tp_getattro = Entity_getAttr;
  PyEntityType.tp_setattro = Entity_setAttr;
  if (PyType_Ready(&PyEntityType) < 0) {
    cout << "Cannot create Entity type" << endl;
    return;
  }

  PyComponentType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyComponentType.tp_doc = "Type of components";
  PyComponentType.tp_new = PyType_GenericNew;
  PyComponentType.tp_methods = Component_methods;
  if (PyType_Ready(&PyComponentType) < 0) {
    cout << "Cannot create Component type" << endl;
    return;
  }

  m = Py_InitModule3("cp", module_Methods,
                     "Chickenpix extension module.");

  // Create Type objects
  Py_INCREF(&PyEntityManagerType);
  PyModule_AddObject(m, "EntityManager", (PyObject *) &PyEntityManagerType);
  Py_INCREF(&PyEntityType);
  PyModule_AddObject(m, "Entity", (PyObject *) &PyEntityType);
  Py_INCREF(&PyComponentType);
  PyModule_AddObject(m, "Component", (PyObject *) &PyComponentType);

  // Constants
  for (int i = 1; ComponentName[i] != NULL; ++i) {
    PyModule_AddObject(m, ComponentName[i], PyInt_FromLong(i));
  }
}

PyObject *wrapEntityManager(EntityManager *em) {
  PyEntityManager *pyem = (PyEntityManager *) PyEntityManagerType.tp_alloc(&PyEntityManagerType, 0);
  pyem->em = em;
  return (PyObject *) pyem;
}

PyObject *wrapEntity(WrappedEntity *e) {
  PyEntity *pye = (PyEntity *) PyEntityType.tp_alloc(&PyEntityType, 0);
  pye->wentity = e;
  return (PyObject *) pye;
}

PyObject *wrapComponent(Component *c) {
  PyComponent *pc = (PyComponent *) PyComponentType.tp_alloc(&PyComponentType, 0);
  pc->component = c;
  return (PyObject *) pc;
}
