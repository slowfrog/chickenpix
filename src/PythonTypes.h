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

class EntityManager;
class WrappedEntity;
class Component;

// EntityManager wrapper
typedef struct {
  PyObject_HEAD
  EntityManager *em;
} PyEntityManager;

extern PyTypeObject PyEntityManagerType;


// Entity wrapper
typedef struct {
  PyObject_HEAD
  WrappedEntity *wentity;
} PyEntity;

extern PyTypeObject PyEntityMType;


// Component wrapper
typedef struct {
  PyObject_HEAD
  Component *component;
} PyComponent;

extern PyTypeObject PyComponentType;


// API
void initcp(EntityManager *em);
PyObject *wrapEntityManager(EntityManager *em);
PyObject *wrapEntity(WrappedEntity  *e);
PyObject *wrapComponent(Component *c);
