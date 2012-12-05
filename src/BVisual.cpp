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
 
#include "BVisual.h"
#include "ComponentRegistry.h"

Component::Type
BVisual::TYPE = VISUAL_TYPE;

BVisual::BVisual(float cx, float cy, int zOrder, bool gui):
  Component(TYPE), cx_(cx), cy_(cy), zOrder_(zOrder), gui_(gui) {
}

BVisual::BVisual(int zOrder, bool gui):
  Component(TYPE), cx_(0), cy_(0), zOrder_(zOrder), gui_(gui) {
}

BVisual::~BVisual() {
}

bool
BVisual::compareZOrder(BVisual const &visual1, BVisual const &visual2) {
  return visual1.zOrder_ < visual2.zOrder_;
}

string
BVisual::toString() const {
  return "{BVisual}";
}
