#include <sstream>
#include <iostream>

#include "SFMLInputs.h"
#include "SFMLVisualContext.h"
#include "../Input.h"
#include "../Transform.h"
#include "../Resources.h"


SFMLInputs::SFMLInputs(string const &name, EntityManager &em):
  Inputs(name, em), window_(NULL), state_(NULL) {
}

SFMLInputs::~SFMLInputs() {
  delete state_;
  state_ = NULL;
}

void
SFMLInputs::init() {
  Resources *resources = _em.getComponent<Resources>();
  SFMLVisualContext &vc = (SFMLVisualContext &) resources->getVisualContext();
  window_ = &vc.getRenderWindow();
  state_ = new SFMLInputState(window_);
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
SFMLInputs::exit() {
}

InputState const *
SFMLInputs::getInputState() const {
  return state_;
}

string
SFMLInputs::toString() const {
  ostringstream out;
  out << "{SFMLInputs-System}" << ends;
  return out.str();
}


