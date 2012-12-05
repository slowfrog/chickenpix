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
#include "Mobile.h"
#include "ComponentRegistry.h"

Component::Type
Mobile::TYPE = MOBILE_TYPE;

Mobile::Mobile():
  Component(TYPE), dx_(0.0f), dy_(0.0f) {
}

Mobile::Mobile(float dx, float dy):
  Component(TYPE), dx_(dx), dy_(dy) {
}

Mobile::~Mobile() {
}

string
Mobile::toString() const {
  ostringstream out;
  out << "{Mobile dx=" << dx_ << ", dy=" << dy_ << "}" << ends;
  return out.str();
};
