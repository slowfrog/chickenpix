/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once

#include <map>

#include "System.h"

typedef struct _object PyObject; // Copied from python/object.h, to avoid inclusion of Python.h

typedef struct {
  PyObject *module;
  PyObject *initFunc;
  PyObject *updateFunc;
  PyObject *exitFunc;
} ScriptInfo;

class Scripting: public System {
private:
  map<string, ScriptInfo> _scriptCache;

  static PyObject *getFunction(PyObject *module, char const *func, string const &moduleName);
  ScriptInfo *getScript(string const &name);
  
public:
  Scripting(string const &name);
  virtual ~Scripting();

  virtual void init   ( EntityManager&);
  virtual void update ( EntityManager&, int now);
  virtual void exit   ( EntityManager&);
  
  virtual string toString() const;
  
  inline SystemType getType() const { return SCRIPTING_TYPE;}
};
