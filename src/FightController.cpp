#include "EntityManager.h"
#include "InputState.h"
#include "Mobile.h"
#include "FightController.h"

void
FightController::update(
                        EntityManager     &em, 
                        Entity            &entity,
                        const InputState  &input, 
                        int               now) 
{
  // manage end of mode
  if (input.isKeyDown(InputState::Q)) {
    // Switch
    em.setSwitch( "Main");
    
    // Move entity to avoid switch again
    Mobile *m = NULL;
    if (!entity.hasComponent(Mobile::TYPE)) {
      m = new Mobile();
      entity.addComponent(m);
    } else {
      m = entity.getComponent<Mobile>();
    }
    m->setSpeed(-50, 0);
  }
}
