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
 
#include <sstream>
#include "Animated.h"
#include "ComponentRegistry.h"

Component::Type
Animated::TYPE = ANIMATED_TYPE;

Animated::Animated(string const &name):
  Component(TYPE), name(name), changed(true) {
}

Animated::~Animated() {
}

string const &
Animated::getAnimation() const {
  return name;
}

void
Animated::setAnimation(string const &anim) {
  if (name != anim) {
    name = anim;
    changed = true;
  }
}

bool
Animated::hasChanged() const {
  return changed;
}

void
Animated::setChanged(bool newChanged) {
  changed = newChanged;
}

string
Animated::toString() const {
  ostringstream out;
  out << "{Animated name=" << name << "}" << ends;
  return out.str();
}
