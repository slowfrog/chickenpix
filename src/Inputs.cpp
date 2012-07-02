#include <sstream>

#include "Controller.h"
#include "Inputs.h"
#include "Input.h"
#include "InputState.h"

Inputs::Inputs(string const &name, EntityManager &em):
  System(name, em), exitRequested_(false), fightMode_(false) {
}

Inputs::~Inputs() {
}

void
Inputs::update(int now) {
  pumpEvents();

  InputState *state = getInputState();
  if (state->isKeyDown(InputState::Escape)) {
    exitRequested_ = true;
    return;
  }
  
  vector<Entity *> entities =_em.getEntities(Input::TYPE);
  for (vector<Entity *>::iterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Input *input = entity->getComponent<Input>();
    input->setInputState(state);

    if (entity->hasComponent(Controller::TYPE)) {
      Controller *c = entity->getComponent<Controller>();
      c->update(now);
    }
  }
  
  //moveHero(now);
}

// void
// Inputs::moveHero(int now) {
//   int dx = 0;
//   int dy = 0;
//   string anim = "man_still";
//   if (isKeyDown(Up)) {
//     dy -= 2;
//     anim = "man_walk_up";
//   }
//   if (isKeyDown(Down)) {
//     dy += 2;
//     anim = "man_walk_down";
//   }
//   if (isKeyDown(Left)) {
//     dx -= 2;
//     anim = "man_walk_left";
//   }
//   if (isKeyDown(Right)) {
//     dx += 2;
//     anim = "man_walk_right";
//   }

//   vector<Entity *> ents = _em.getEntities(Mobile::TYPE, Input::TYPE);
//   for (vector<Entity *>::iterator it = ents.begin(); it < ents.end(); it++) {
//     Entity *ent = *it;
//     Mobile *m = ent->getComponent<Mobile>();
//     m->setSpeed((float) dx, (float) dy);
//   }
// }

bool
Inputs::isExitRequested() const {
  return exitRequested_;
}

string
Inputs::toString() const {
  ostringstream out;
  out << "{Inputs-System}" << ends;
  return out.str();
}


