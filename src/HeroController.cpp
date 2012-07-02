#include "HeroController.h"
#include "Entity.h"
#include "Input.h"
#include "InputState.h"
#include "Mobile.h"
#include "Resources.h"
#include "log.h"

HeroController::HeroController() :
  Controller() {
}

HeroController::~HeroController() {
}

void
HeroController::update(int now) {
  Entity *entity = getEntity();
  if (entity == NULL) {
    LOG2 << "Missing entity for HeroController\n";
    return;
  }
  
  if (!entity->hasComponent(Input::TYPE)) {
    LOG2 << "Missing Input component for HeroController " << entity << "\n";
    return;
  }
  const InputState *input = entity->getComponent<Input>()->getInputState();
  
  float dx = 0;
  float dy = 0;
  if (input->isKeyDown(InputState::Up)) {
    dy -= 2;
  }
  if (input->isKeyDown(InputState::Down)) {
    dy += 2;
  }
  if (input->isKeyDown(InputState::Left)) {
    dx -= 2;
  }
  if (input->isKeyDown(InputState::Right)) {
    dx += 2;
  }

  Mobile *m = entity->hasComponent(Mobile::TYPE) ? entity->getComponent<Mobile>() : new Mobile();
  m->setSpeed(dx, dy);
}

string
HeroController::toString() const {
  return "{HeroController}";
}


