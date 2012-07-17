#include "EntityManager.h"
#include "InputState.h"
#include "Mobile.h"
#include "Collider.h"
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
  }
  
  // Manage "continue"
  if (input.isKeyDown(InputState::C)) {
    return;
  }
}
