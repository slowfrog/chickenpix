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
class Collider;

class Movement: public System {
private:
  int prev_;
  
public:
  Movement( string const &name);
  virtual ~Movement();

  virtual void init   ( EntityManager &);
  virtual void update ( EntityManager &, int now);
  virtual void exit   ( EntityManager &);
  
  inline SystemType getType() const { return MOVEMENT_TYPE;}

  virtual string toString() const;

private:
  void clearCollisions(EntityManager &em) const;
  bool resolveCollisions(EntityManager &em, Entity *ecol, Collider *col,
                         float dx, float dy,
                         float &dxAllowed, float &dyAllowed) const;
  static bool overlap(float minx1, float maxx1, float miny1, float maxy1,
                      float minx2, float maxx2, float miny2, float maxy2);
  static bool collide(Entity *ecol1, Collider *col1,
                      Entity *ecol2, Collider *col2,
                      float dx, float dy, float &dxAllowed, float &dyAllowed);
};
