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
#include "VisualContext.h"

class Render: public System {
private:
  int last;
public:
  Render( string const &name);
  virtual ~Render();

  // System interface
  virtual void init   ( EntityManager&) = 0;
  virtual void update ( EntityManager&, int now);
  virtual void exit   ( EntityManager&) = 0;
  
  // Render interface
  virtual VisualContext *getVisualContext() = 0;
  virtual void clear( VisualContext &vc) = 0;
  virtual void paint( VisualContext &vc) = 0;
  
  
  inline SystemType getType() const { return RENDER_TYPE;}

  virtual string toString() const;

private:
  void applyCameraConstraints(EntityManager &em, Entity *cameraEntity);
};
