#include "EntityManager.h"
#include "InputState.h"
#include "Mobile.h"
#include "Collider.h"
#include "Actionable.h"
#include "FightSystem.h"
#include "FightController.h"

void
FightController::update(
                        EntityManager     &em, 
                        Entity            &entity,
                        const InputState  &input, 
                        int               now) 
{
  // Mother call first
  ButtonController::update( em, entity, input, now);
  
  // manage end of mode
  if (input.isKeyDown(InputState::Q)) {
    // Quit fight mode
    NotificationCenter::get()->Notify( FS_NOTIFIER_QUIT);
    // Reset entity manager (fight mode)
    //em.destroyAllEntitiesExcept("mandatory");
    //em.destroyEntity
    // Switch
    //em.setSwitch( "Main");
  }
  
  // Manage "continue"
  if (input.isKeyDown(InputState::A)) {
    //NotificationCenter::get()->Notify( FS_NOTIFIER_SKILL);
  }
  
  Actionable *act = em.getComponent<Actionable>();
  if ( act && act->getAction() == "ButtonClicked"){
    InputState::MousePos mpos = input.getMousePosition();
    LOG2 << "Button cliked in Fight Mode\n";
    NotificationCenter::get()->Notify( FS_NOTIFIER_SKILL);
  }
}

//void FightController::checkPos( const InputState::MousePos &pos){
  //if ( ) {
  //  <#statements#>
  //}
//}
