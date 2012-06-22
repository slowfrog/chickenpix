#pragma once

#include <map>

#include "System.h"

typedef struct _object PyObject; // Copied from python/object.h, to avoid inclusion of Python.h

typedef struct {
  PyObject *module;
  PyObject *func;
} ScriptInfo;

class Scripting: public System {
private:
  map<string, ScriptInfo> scriptCache;

  ScriptInfo *getScript(string const &name);
  
public:
  Scripting(string const &name, EntityManager &em);
  virtual ~Scripting();

  virtual void init();
  virtual void update(int now);
  virtual void exit();
  virtual string toString() const;
};
