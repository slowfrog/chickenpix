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
#include <vector>
#include "Component.h"
#include "Image.h"

class Animated: public Component {
private:
  string name;
  bool changed;
  
public:
  static Type TYPE;

  Animated(string const &name);
  virtual ~Animated();

  string const &getAnimation() const;
  void setAnimation(string const &anim);
  bool hasChanged() const;
  void setChanged(bool changed);
  
  virtual string toString() const;
};
