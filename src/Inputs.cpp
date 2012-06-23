#include <sstream>

#include "Animated.h"
#include "Inputs.h"
#include "Input.h"
#include "Resources.h"
#include "Transform.h"

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
    dy -= 1;
    anim = "man_walk_up";
  }
  if (isKeyDown(Down)) {
    dy += 1;
    anim = "man_walk_down";
  }
  if (isKeyDown(Left)) {
    dx -= 1;
    anim = "man_walk_left";
  }
  if (isKeyDown(Right)) {
    dx += 1;
    anim = "man_walk_right";
  }

  vector<Entity *> ents = em.getEntities(Input::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = ents.begin(); it < ents.end(); it++) {
    Entity *ent = *it;
    if ((dx != 0) || (dy != 0)) {
      Transform *t = ent->getComponent<Transform>();
      t->moveBy((float) dx, (float) dy);
    }

    if (ent->hasComponent(Animated::TYPE)) {
      Animated *animated = ent->getComponent<Animated>();
      animated->setAnimation(anim);
    }
  }
  
};

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


