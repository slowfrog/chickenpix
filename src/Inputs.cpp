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

  InputState const *state = getInputState();
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
}

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


