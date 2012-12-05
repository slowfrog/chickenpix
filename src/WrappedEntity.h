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
#include <Python.h>
#include "Entity.h"
#include "PythonTypes.h"

class WrappedEntity: public Entity {
private:
  PyObject *_wrapper;
  PyObject *_dict;
public:
  static const Type TYPE; // = 2
  
  WrappedEntity(Entity &src);
  virtual ~WrappedEntity();

  static WrappedEntity *wrap(EntityManager &em, Entity *entity);
  
  inline
  static bool isInstance(Entity *entity) {
    return entity->getType() == TYPE;
  }
  
  PyObject *getWrapper() const;

  // Free dictionary of values used by scripts
  PyObject *getDict() const;
  PyObject *getOrCreateDict();
  int setItem(PyObject *key, PyObject *val);
  int delItem(PyObject *key);
  int contains(PyObject *key);
  PyObject *getItem(PyObject *key);
};
