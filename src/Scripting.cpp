#include <Python.h>

#include <iostream>
#include <sstream>

#include "Scripting.h"
#include "Scriptable.h"
#include "PythonTypes.h"
#include "WrappedEntity.h"

Scripting::Scripting(string const &name, EntityManager &em):
  System(name, em) {
}

Scripting::~Scripting() {
  for (map<string, ScriptInfo>::iterator it = _scriptCache.begin(); it != _scriptCache.end(); it++) {
    ScriptInfo &info = it->second;
    Py_DECREF(info.func);
    Py_DECREF(info.module);
  }
  _scriptCache.clear();
}

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
  initcp(&_em);
}

ScriptInfo *
Scripting::getScript(string const &name) {
  // If we want dynamic reloading of scripts, we should check here
  if (_scriptCache.find(name) == _scriptCache.end()) {
    PyObject *pName = PyString_FromString(name.c_str());
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (!pModule) {
      cout << "Could not load module " << name << endl;
      if (PyErr_Occurred()) {
        PyErr_Print();
      }
      return NULL;
    }
    PyObject *pFunc = PyObject_GetAttrString(pModule, "run");
    if (!pFunc) {
      cout << "'" << "run" << "' is not found in module " << name << endl;
      Py_DECREF(pModule);
      return NULL;
    } else if (!PyCallable_Check(pFunc)) {
      cout << "'" << "run" << "' is not callable in module " << name << endl;
      Py_DECREF(pModule);
      return NULL;
      
    } else {
      ScriptInfo info = {pModule, pFunc};
      _scriptCache[name] = info;
    }
  }
  return &_scriptCache[name];
}

void
Scripting::update(int now) {
  PyObject *pyem = wrapEntityManager(&_em);

  vector<Entity *> scripts = _em.getEntities(Scriptable::TYPE);
  for (vector<Entity *>::iterator it = scripts.begin(); it < scripts.end(); it++) {

    WrappedEntity *wentity = WrappedEntity::wrap(_em, *it);
    Scriptable *scriptable = wentity->getComponent<Scriptable>();
    ScriptInfo *info = getScript(scriptable->getName());
    if (info) {
      scriptable->update(now); // ??

      PyObject *pye = wentity->getWrapper();
      PyObject *arglist = Py_BuildValue("(OO)", pye, pyem);
      PyObject *ret = PyObject_CallObject(info->func, arglist);

      Py_DECREF(arglist);
      if (PyErr_Occurred()) {
        cout << "#Error from CallObject" << endl;
        PyErr_Print();
      }
      if (ret) {
        Py_DECREF(ret);
      }
    }
  }
  Py_DECREF(pyem);
}

void
Scripting::exit() {
  Py_Finalize();
}

string
Scripting::toString() const {
  ostringstream out;
  out << "{Scripting-System name=" << getName() << "}" << ends;
  return out.str();
}
