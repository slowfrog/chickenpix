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
 
#include "Resources.h"
#include "ComponentRegistry.h"

CPColor
CPColor::White(255, 255, 255);

Component::Type
Resources::TYPE = RESOURCES_TYPE;

Resources::Resources():
  Component(TYPE) {
}

Resources::~Resources() {
  // Should destroy all resources, because this object is supposed to be the owner
}

void
Resources::setObject(Kind kind, string const &name, ResBase *object) {
  store[kind][name] = object;
}

ResBase *
Resources::getObject(Kind kind, string const &name) {
  return store[kind][name];
}

string
Resources::toString() const {
  return "{Resources}";
}
