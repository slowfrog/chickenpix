#include "log.h"
#include "HeroController.h"
#include "Entity.h"
#include "InputState.h"
#include "Mobile.h"
#include "Resources.h"

void
HeroController::update(EntityManager &em, Entity &entity,
                       const InputState &input, int now) {
  float dx = 0;
  float dy = 0;
  if (input.isKeyDown(InputState::Up)) {
    dy -= 2;
  }
  if (input.isKeyDown(InputState::Down)) {
    dy += 2;
  }
  if (input.isKeyDown(InputState::Left)) {
    dx -= 2;
  }
  if (input.isKeyDown(InputState::Right)) {
    dx += 2;
  }

  Mobile *m = NULL;
  if (!entity.hasComponent(Mobile::TYPE)) {
    m = new Mobile();
    entity.addComponent(m);
  } else {
    m = entity.getComponent<Mobile>();
  }
  m->setSpeed(dx, dy);
}
