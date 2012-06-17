#include <sstream>

#include <ClanLib/core.h>

#include "CLInputs.h"
#include "CLState.h"
#include "Input.h"
#include "Transform.h"

CLInputs::CLInputs(string const &name, EntityManager &em):
  System(name, em), exitRequested(false), keyboard(NULL) {
}

CLInputs::~CLInputs() {
}

void
CLInputs::init() {
  CLState *clstate = em.getComponent<CLState>();
  keyboard = &(clstate->getWindow().get_ic().get_keyboard());
}

void
CLInputs::update(int now) {
  bool escape_down = keyboard->get_keycode(CL_KEY_ESCAPE);
  if (escape_down) {
    exitRequested = true;
  }

  moveHero(now);
  
  // Read messages from the windowing system message queue, if any are available:
  CL_KeepAlive::process();
}

void
CLInputs::moveHero(int now) {
  int dx = 0;
  int dy = 0;
  string anim = "man_still";
  if (keyboard->get_keycode(CL_KEY_UP)) {
    dy -= 1;
    anim = "man_walk_up";
  }
  if (keyboard->get_keycode(CL_KEY_DOWN)) {
    dy += 1;
    anim = "man_walk_down";
  }
  if (keyboard->get_keycode(CL_KEY_LEFT)) {
    dx -= 1;
    anim = "man_walk_left";
  }
  if (keyboard->get_keycode(CL_KEY_RIGHT)) {
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
CLInputs::exit() {
}

bool
CLInputs::isExitRequested() const {
  return exitRequested;
}

string
CLInputs::toString() const {
  ostringstream out;
  out << "{CLInputs-System}" << ends;
  return out.str();
}


