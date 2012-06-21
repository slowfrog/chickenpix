#include <sstream>
#include <iostream>

#include <SFML/Window.hpp>

#include "SFMLInputs.h"
#include "SFMLState.h"
#include "../Input.h"
#include "../Transform.h"

sf::Key::Code KEYMAP[] = {
  sf::Key::Num0,
  sf::Key::Num1,
  sf::Key::Num2,
  sf::Key::Num3,
  sf::Key::Num4,
  sf::Key::Num5,
  sf::Key::Num6,
  sf::Key::Num7,
  sf::Key::Num8,
  sf::Key::Num9,
  sf::Key::Space,
  sf::Key::Up,
  sf::Key::Down,
  sf::Key::Left,
  sf::Key::Right,
  sf::Key::Escape,
};


SFMLInputs::SFMLInputs(string const &name, EntityManager &em):
  Inputs(name, em), window(NULL) {
}

SFMLInputs::~SFMLInputs() {
}

void
SFMLInputs::init() {
  SFMLState *state = em.getComponent<SFMLState>();
  window = &state->getWindow();
}

void
SFMLInputs::pumpEvents() {
  sf::Event event;
  while (window->GetEvent(event)) {
    if (event.Type == sf::Event::Closed) {
      exitRequested = true;
      return;
    }
  }
}

bool
SFMLInputs::isKeyDown(Key key) const {
  return window->GetInput().IsKeyDown(KEYMAP[key]);
}

void
SFMLInputs::exit() {
}

string
SFMLInputs::toString() const {
  ostringstream out;
  out << "{SFMLInputs-System}" << ends;
  return out.str();
}


