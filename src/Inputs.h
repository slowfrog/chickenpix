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

class InputState;

class Inputs: public System {
protected:
  bool exitRequested_;
  // Game state
  bool  fightMode_;
public:
  Inputs(string const &name);
  virtual ~Inputs();

  virtual void init   ( EntityManager &em);
  virtual void update ( EntityManager &em, int now);
  virtual void exit   ( EntityManager &em) = 0;
  
  virtual void pumpEvents() = 0;
  virtual InputState const *getInputState() const = 0;

  bool isExitRequested() const;
  
  inline SystemType getType() const { return INPUTS_TYPE;}
  
  virtual string toString() const;

private:
  // Round fight
  void initiateFight(int now);
};
