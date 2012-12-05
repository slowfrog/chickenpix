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
#include <iostream>

#include "SFMLInputs.h"
#include "SFMLVisualContext.h"
#include "../Input.h"
#include "../Transform.h"
#include "../Resources.h"


SFMLInputs::SFMLInputs( string const &name):
  Inputs( name), window_(NULL), state_(NULL) {
}

SFMLInputs::~SFMLInputs() {
  delete state_;
  state_ = NULL;
}

void
SFMLInputs::init( EntityManager &em) {
  Inputs::init( em);
  Resources *resources = em.getComponent<Resources>();
  SFMLVisualContext &vc = (SFMLVisualContext &) resources->getVisualContext();
  window_ = &vc.getRenderWindow();
  state_ = new SFMLInputState(vc, window_);
}

void
SFMLInputs::pumpEvents() {
  sf::Event event;
  while (window_->GetEvent(event)) {
    // if (event.Type == sf::Event::Closed) {
    //   exitRequested = true;
    //   return;
    // }
  }
}

void
SFMLInputs::exit( EntityManager&) {
}

InputState const *
SFMLInputs::getInputState() const {
  return state_;
}

string
SFMLInputs::toString() const {
  ostringstream out;
  out << "{SFMLInputs-System " << getName() << "}" << ends;
  return out.str();
}


