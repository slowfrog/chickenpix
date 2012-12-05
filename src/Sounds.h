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

#include "System.h"

class EntityManager;

class Sounds: public System {
public:
  Sounds(const string &name);
  virtual ~Sounds();

  virtual void init   ( EntityManager &em);
  virtual void update ( EntityManager &em, int now);
  virtual void exit   ( EntityManager &em);

  inline
  virtual SystemType getType() const {
    return SOUNDS_TYPE;
  }

  virtual string toString() const;
};
