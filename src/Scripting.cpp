#include <Python.h>

#include <iostream>
#include <sstream>

#include "Scripting.h"
#include "Scriptable.h"
#include "PythonTypes.h"
#include "WrappedEntity.h"

Scripting::Scripting(string const &name):
  System( name) {
}

Scripting::~Scripting() {
  for (map<string, ScriptInfo>::iterator it = _scriptCache.begin(); it != _scriptCache.end(); it++) {
    ScriptInfo &info = it->second;
    Py_XDECREF(info.initFunc);
    Py_XDECREF(info.updateFunc);
    Py_XDECREF(info.exitFunc);
    Py_DECREF(info.module);
  }
  _scriptCache.clear();
}

void
Scripting::init( EntityManager &em) {
  Py_NoSiteFlag = 1;
  Py_Initialize();

  PyObject *sys_path;
  PyObject *path;
  sys_path = PySys_GetObject((char *)"path");
  if (sys_path) {
    path = PyString_FromString("resources/scripts");
    if (PyList_Append(sys_path, path) < 0) {
      cout << "Could not append to path" << endl;
    }
    Py_DECREF(path);
  }
  initcp(&em);
}

PyObject *
Scripting::getFunction(PyObject *module, char const *func, string const &moduleName) {
  PyObject *pFunc = PyObject_GetAttrString(module, func);
  if (!pFunc) {
    return NULL;
    
  } else if (!PyCallable_Check(pFunc)) {
    cout << "'" << func << "' is not callable in module " << moduleName << endl;
    return NULL;
    
  } else {
    return pFunc;
  }
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
    PyObject *initFunc = getFunction(pModule, "init", name);
    PyObject *updateFunc = getFunction(pModule, "update", name);
    PyObject *exitFunc = getFunction(pModule, "exit", name);
    ScriptInfo info = {pModule, initFunc, updateFunc, exitFunc};
    _scriptCache[name] = info;
  }
  return &_scriptCache[name];
}

void
Scripting::update(EntityManager &em, int now) {
  PyObject *pyem = wrapEntityManager(&em);

  vector<Entity *> scripts = em.getEntities(Scriptable::TYPE);
  for (vector<Entity *>::iterator it = scripts.begin(); it < scripts.end(); it++) {

    WrappedEntity *wentity = WrappedEntity::wrap( em, *it);
    Scriptable *scriptable = wentity->getComponent<Scriptable>();
    ScriptInfo *info = getScript(scriptable->getName());
    if (info) {
      PyObject *pye = wentity->getWrapper();
      PyObject *arglist = Py_BuildValue("(OO)", pye, pyem);

      if (!(scriptable->isInitDone() || info->initFunc == NULL)) {
        PyObject *ret = PyObject_CallObject(info->initFunc, arglist);
        scriptable->setInitDone(true);
        if (PyErr_Occurred()) {
          cout << "#Error from " << scriptable->getName() << ".init()" << endl;
          PyErr_Print();
        }
        if (ret) {
          Py_DECREF(ret);
        }
      }
      
      scriptable->update(now); // Useless ?

      if (info->updateFunc != NULL) {
        PyObject *ret = PyObject_CallObject(info->updateFunc, arglist);
        if (PyErr_Occurred()) {
          cout << "#Error from " << scriptable->getName() << ".update()" << endl;
          PyErr_Print();
        }
        if (ret) {
          Py_DECREF(ret);
        }
      }
      Py_DECREF(arglist);
    }
  }
  Py_DECREF(pyem);
}

void
Scripting::exit( EntityManager&) {
  Py_Finalize();
}

string
Scripting::toString() const {
  ostringstream out;
  out << "{Scripting-System name=" << getName() << "}" << ends;
  return out.str();
}
