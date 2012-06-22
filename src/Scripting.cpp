#include <Python.h>
#include <iostream>
#include <sstream>

#include "Scripting.h"
#include "Scriptable.h"
#include "PythonTypes.h"

Scripting::Scripting(string const &name, EntityManager &em):
  System(name, em) {
}

Scripting::~Scripting() {
}

// static PyObject *
// ss(PyObject *self, PyObject *args) {
//   PyObject *obj;
//   if (!PyArg_ParseTuple(args, "O", &obj)) {
//     cout << "Error parsing arguments." << endl;
//     return Py_None;
//   }
//   EntityManager *em = (EntityManager *) PyCObject_AsVoidPtr(obj);
//   cout << em->toString() << endl;
//   return Py_None;
// }

// static PyMethodDef EmbeddedMethods[] = {
//   {"ss", ss, METH_VARARGS, "Get something"},
//   {NULL, NULL, 0, NULL}
// };

// static PyObject *EmCapsule;
// static PyObject *CPModule;

void
Scripting::init() {
  Py_NoSiteFlag = 1;
  Py_Initialize();

  PyObject *sys_path;
  PyObject *path;
  sys_path = PySys_GetObject((char *)"path");
  if (sys_path) {
    path = PyString_FromString(".");
    if (PyList_Append(sys_path, path) < 0) {
      cout << "Could not append to path" << endl;
    }
    Py_DECREF(path);
  }
  initcp(&em);
  
  /*CPModule = Py_InitModule("cp0", EmbeddedMethods);
  if (!CPModule) {
    cout << "Could not create module" << endl;
    return;
  }
  EmCapsule = PyCObject_FromVoidPtr(&em, NULL);
  if (!EmCapsule) {
    cout << "Could not create Capsule" << endl;
    return;
  } else {
    cout << "Capsule created with " << PyCObject_AsVoidPtr(EmCapsule) << endl;
  }
  if (PyModule_AddObject(CPModule, "em", EmCapsule)) {
    cout << "Error adding \"em\" to module" << endl;
  } else {
    cout << "Module ok and \"em\" available" << endl;
    }*/
}

void
Scripting::update(int now) {
  PyObject *pName = PyString_FromString("toby");
  PyObject *pModule = PyImport_Import(pName);
  Py_DECREF(pName);
  if (!pModule) {
    cout << "Could not load module" << endl;
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return;
  }
  PyObject *pFunc = PyObject_GetAttrString(pModule, "run");
  if ((!pFunc) || (!PyCallable_Check(pFunc))) {
    cout << "pFunc is not callable" << endl;
  } else {
    //cout << "Capsule ok with " << PyCObject_AsVoidPtr(EmCapsule) << endl;

    
    PyObject *pyem = wrapEntityManager(&em);

    vector<Entity *> scripts = em.getEntities(Scriptable::TYPE);
    for (vector<Entity *>::iterator it = scripts.begin(); it < scripts.end(); it++) {
      Entity *entity = *it;
      Scriptable *s = entity->getComponent<Scriptable>();
      s->update(now); // ??

      PyObject *pye = wrapEntity(entity);
      PyObject *arglist = Py_BuildValue("(OO)", pye, pyem);
      PyObject *ret = PyObject_CallObject(pFunc, arglist);
      Py_DECREF(arglist);
      Py_DECREF(pye);
      if (PyErr_Occurred()) {
        PyErr_Print();
      }
      if (ret) {
        Py_DECREF(ret);
      }
    }
    Py_DECREF(pyem);
  }
}

void
Scripting::exit() {
  Py_Finalize();
}

string
Scripting::toString() const {
  ostringstream out;
  out << "{Scripting-System name=" << name << "}" << ends;
  return out.str();
}
