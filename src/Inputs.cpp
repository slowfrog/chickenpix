/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <sstream>

#include "log.h"
#include "Controller.h"
#include "HeroController.h"
#include "ButtonController.h"
#include "FightController.h"
#include "Inputs.h"
#include "Input.h"
#include "InputState.h"

Inputs::Inputs( string const &name):
  System( name), exitRequested_(false), fightMode_(false) {
}

Inputs::~Inputs() {
}

typedef void (*ControllerUpdate)(EntityManager &, Entity &,
                                 InputState const &, int);

static map<string, ControllerUpdate> CONTROLLERS;

void
Inputs::init( EntityManager &em) {
  CONTROLLERS["HeroController"]   = HeroController::update;
  CONTROLLERS["ButtonController"] = ButtonController::update;
  CONTROLLERS["FightController"]  = FightController::update;
}

void
Inputs::update(EntityManager &em, int now) {
  pumpEvents();

  InputState const *state = getInputState();
  exitRequested_ = state->isKeyDown(InputState::Escape);
  
  vector<Entity *> entities = em.getEntities(Input::TYPE);
  for (vector<Entity *>::iterator it = entities.begin();
       it < entities.end(); ++it) {
    Entity *entity = *it;
    Input *input = entity->getComponent<Input>();
    input->setInputState(state);
  }

  if (exitRequested_) {
    LOG2 << "Exit requested at " << now << "\n";
    return;
  }

  entities = em.getEntities(Controller::TYPE);
  for (vector<Entity *>::iterator it = entities.begin();
       it < entities.end(); ++it) {
    Entity *entity = *it;
    Controller *c = entity->getComponent<Controller>();
    const vector<string> &names = c->getNames();
    for (unsigned int i = 0; i < names.size(); ++i) {
      const string &name = names[i];
      if (CONTROLLERS.find(name) != CONTROLLERS.end()) {
        CONTROLLERS[name]( em, *entity, *state, now);
      } else {
        // TODO find a script with the right name
        LOG2 << "Controller not found for name: " << name << "\n";
      }
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


