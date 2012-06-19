#include <sstream>
#include <iostream>

#include <SFML/Window.hpp>

#include "SFMLInputs.h"
#include "SFMLState.h"
#include "Input.h"
#include "Transform.h"

SFMLInputs::SFMLInputs(string const &name, EntityManager &em):
  System(name, em), window(NULL), exitRequested(false) {
}

SFMLInputs::~SFMLInputs() {
}

void
SFMLInputs::init() {
  SFMLState *state = em.getComponent<SFMLState>();
  window = &state->getWindow();
  //keyboard = &(clstate->getWindow().get_ic().get_keyboard());
}

void
SFMLInputs::update(int now) {
  sf::Event event;
  while (window->GetEvent(event)) {
    if (event.Type == sf::Event::Closed) {
      exitRequested = true;
      return;
    }
  }

  sf::Input const &input = window->GetInput();
  bool escape_down = input.IsKeyDown(sf::Key::Escape);
  if (escape_down) {
    exitRequested = true;
  }

  moveHero(now);
}

void
SFMLInputs::moveHero(int now) {
  int dx = 0;
  int dy = 0;
  string anim = "man_still";
  sf::Input const &input = window->GetInput();
  if (input.IsKeyDown(sf::Key::Up)) {
    dy -= 1;
    anim = "man_walk_up";
  }
  if (input.IsKeyDown(sf::Key::Down)) {
    dy += 1;
    anim = "man_walk_down";
  }
  if (input.IsKeyDown(sf::Key::Left)) {
    dx -= 1;
    anim = "man_walk_left";
  }
  if (input.IsKeyDown(sf::Key::Right)) {
    dx += 1;
    anim = "man_walk_right";
  }
  
  vector<Entity *> ents = em.getEntities(Input::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = ents.begin(); it < ents.end(); it++) {
    Entity *ent = *it;
    if ((dx != 0) || (dy != 0)) {
      Transform *t = ent->getComponent<Transform>();
      t->moveBy(dx, dy);
    }

    // Apply animation if possible...
  }
  
};

void
SFMLInputs::exit() {
}

bool
SFMLInputs::isExitRequested() const {
  return exitRequested;
}

string
SFMLInputs::toString() const {
  ostringstream out;
  out << "{SFMLInputs-System}" << ends;
  return out.str();
}


