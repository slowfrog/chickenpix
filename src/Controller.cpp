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
#include "Controller.h"
#include "ComponentRegistry.h"

Component::Type
Controller::TYPE = CONTROLLER_TYPE;

Controller::Controller(const string &name):
  Component(Controller::TYPE) {
  addName(name);
}

Controller::~Controller() {
}

void
Controller::addName(const string &name) {
  for (vector<string>::const_iterator it = names_.begin(); it < names_.end();
       ++it) {
    if (name == *it) {
      return;
    }
  }
  names_.push_back(name);
}

void
Controller::removeName(const string &name) {
  for (vector<string>::iterator it = names_.begin(); it < names_.end();
       ++it) {
    if (name == *it) {
      names_.erase(it);
      return;
    }
  }
}

string
Controller::toString() const {
  ostringstream out;
  out << "{Controller [ ";
  for (vector<string>::const_iterator it = names_.begin(); it < names_.end();
       ++it) {
    out << (*it) << " ";
  }
  out << "]}" << ends;
  return out.str();
}
