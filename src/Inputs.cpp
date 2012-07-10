#include <sstream>

#include "log.h"
#include "Controller.h"
#include "HeroController.h"
#include "ButtonController.h"
#include "Inputs.h"
#include "Input.h"
#include "InputState.h"

Inputs::Inputs( string const &name):
  System( name), exitRequested_(false), fightMode_(false) {
}

Inputs::~Inputs() {
}

static map<string, void(*)(EntityManager &, Entity &, InputState const &, int)>
CONTROLLERS;

void
Inputs::init( EntityManager &em) {
  CONTROLLERS["HeroController"] = HeroController::update;
  CONTROLLERS["ButtonController"] = ButtonController::update;
}

void
Inputs::update(EntityManager &em, int now) {
  pumpEvents();

  InputState const *state = getInputState();
  if (state->isKeyDown(InputState::Escape)) {
    exitRequested_ = true;
  }
  
  vector<Entity *> entities = em.getEntities(Input::TYPE);
  for (vector<Entity *>::iterator it = entities.begin();
       it < entities.end(); ++it) {
    Entity *entity = *it;
    Input *input = entity->getComponent<Input>();
    input->setInputState(state);
  }

  if (exitRequested_) {
    return;
  }

  entities = em.getEntities(Controller::TYPE);
  for (vector<Entity *>::iterator it = entities.begin();
       it < entities.end(); ++it) {
    Entity *entity = *it;
    Controller *c = entity->getComponent<Controller>();
    const string &name = c->getName();
    if (CONTROLLERS.find(name) != CONTROLLERS.end()) {
      CONTROLLERS[name]( em, *entity, *state, now);
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


