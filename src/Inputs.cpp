#include <sstream>

#include "Animated.h"
#include "Inputs.h"
#include "Input.h"
#include "Resources.h"
#include "Mobile.h"

Inputs::Inputs(string const &name, EntityManager &em):
  System(name, em), exitRequested(false) {
}

Inputs::~Inputs() {
}

void
Inputs::update(int now) {
  pumpEvents();
  
  bool escape_down = isKeyDown(Escape);
  if (escape_down) {
    exitRequested = true;
  }

  moveHero(now);
}

void
Inputs::moveHero(int now) {
  int dx = 0;
  int dy = 0;
  string anim = "man_still";
  if (isKeyDown(Up)) {
    dy -= 2;
    anim = "man_walk_up";
  }
  if (isKeyDown(Down)) {
    dy += 2;
    anim = "man_walk_down";
  }
  if (isKeyDown(Left)) {
    dx -= 2;
    anim = "man_walk_left";
  }
  if (isKeyDown(Right)) {
    dx += 2;
    anim = "man_walk_right";
  }

  vector<Entity *> ents = _em.getEntities(Mobile::TYPE, Input::TYPE);
  for (vector<Entity *>::iterator it = ents.begin(); it < ents.end(); it++) {
    Entity *ent = *it;
    Mobile *m = ent->getComponent<Mobile>();
    m->setSpeed((float) dx, (float) dy);
  }
}

bool
Inputs::isExitRequested() const {
  return exitRequested;
}

string
Inputs::toString() const {
  ostringstream out;
  out << "{Inputs-System}" << ends;
  return out.str();
}


