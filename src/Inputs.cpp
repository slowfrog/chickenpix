#include <sstream>

#include "log.h"
#include "Controller.h"
#include "HeroController.h"
#include "ButtonController.h"
#include "Inputs.h"
#include "Input.h"
#include "InputState.h"

Inputs::Inputs(string const &name, EntityManager &em):
  System(name, em), exitRequested_(false), fightMode_(false) {
}

Inputs::~Inputs() {
}

static map<string, void(*)(EntityManager &, Entity &, InputState const &, int)>
CONTROLLERS;

void
Inputs::init() {
  CONTROLLERS["HeroController"] = HeroController::update;
  CONTROLLERS["ButtonController"] = ButtonController::update;
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
  for (vector<Entity *>::iterator it = entities.begin();
       it < entities.end(); ++it) {
    Entity *entity = *it;
    Input *input = entity->getComponent<Input>();
    input->setInputState(state);
  }

  entities = _em.getEntities(Controller::TYPE);
  for (vector<Entity *>::iterator it = entities.begin();
       it < entities.end(); ++it) {
    Entity *entity = *it;
    Controller *c = entity->getComponent<Controller>();
    const string &name = c->getName();
    if (CONTROLLERS.find(name) != CONTROLLERS.end()) {
      CONTROLLERS[name](_em, *entity, *state, now);
    } else {
      // TODO find a script with the right name
      LOG2 << "Controller not found for name: " << name << "\n";
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


