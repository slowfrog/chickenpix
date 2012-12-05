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

#include "CLInputs.h"
#include "CLVisualContext.h"
#include "../Input.h"
#include "../Resources.h"
#include "../Transform.h"

CLInputs::CLInputs(string const &name):
  Inputs(name), keyboard_(NULL), mouse_(NULL), state_(NULL) {
}

CLInputs::~CLInputs() {
  delete state_;
  state_ = NULL;
}

void
CLInputs::init(EntityManager &em) {
  Inputs::init(em);
  Resources *resources = em.getComponent<Resources>();
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  keyboard_ = &(vc.getWindow().get_ic().get_keyboard());
  mouse_ = &(vc.getWindow().get_ic().get_mouse());
  state_ = new CLInputState(vc, keyboard_, mouse_);
}

void
CLInputs::pumpEvents() {
  // Read messages from the windowing system message queue, if any are available:
  CL_KeepAlive::process();
}

InputState const *
CLInputs::getInputState() const {
  return state_;
}

void
CLInputs::exit(EntityManager &em) {
}

string
CLInputs::toString() const {
  ostringstream out;
  out << "{CLInputs-System " << getName() << "}" << ends;
  return out.str();
}


