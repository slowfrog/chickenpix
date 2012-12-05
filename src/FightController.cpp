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
 
#include "EntityManager.h"
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
  }
  
  // Manage "continue"
  //if (input.isKeyDown(InputState::A)) {
    //NotificationCenter::get()->Notify( FS_NOTIFIER_SKILL);
  //}
  
  Actionable *act = em.getComponent<Actionable>();
  if ( act && act->getAction() == "ButtonClicked"){
    InputState::MousePos mpos = input.getMousePosition();
    checkPos( mpos);
    LOG2 << "Button cliked in Fight Mode\n";
    //NotificationCenter::get()->Notify( FS_NOTIFIER_SKILL);
  }
}

void 
FightController::checkPos( const InputState::MousePos &pos){
  LOG2<<"Pos x:"<<pos.x<<" et pos y:"<<pos.y<<"\n";
  // Attack
  if (      pos.x >= 20 && pos.x <= 74
        &&  pos.y >= 314 && pos.y <= 378) {
    NotificationCenter::get()->Notify( FS_NOTIFIER_SKILL);
  }
  // Quit
  if (      pos.x >= 86 && pos.x <= 150
        &&  pos.y >= 314 && pos.y <= 378) {
    NotificationCenter::get()->Notify( FS_NOTIFIER_QUIT);
  }
}
