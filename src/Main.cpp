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
 
#include "Main.h"

// Prepare fight
void prepareFight( EntityManager &em, CFightSystem *fs)
{  
  // Check Mode
  if ( em.getName() != FIGHT){
    return;
  }
  // Prepare round
  fs->reset();
  CTagEntityMng::TEntityId id = em.getTagMng().getFirstEntityByTag( "HERO");
  Entity *e = em.getById( id);
  if ( e){
    Character *c = e->getComponent<Character>();
    if ( NULL == c)
      return;
    
    // Add fighter
    fs->addAlly( *c);
  }
  
  TEntityIdList vid = em.getByTag( "FoeInFight");
  if ( !vid.empty()){
    TEntityIdList::iterator it = vid.begin();
    for( ; it != vid.end(); it++){
      Entity *e = em.getById( (*it));
      if ( e){
        Character *c = e->getComponent<Character>();
        if ( NULL == c)
          return;
        
        // Add fighter
        fs->addFoe( *c);
      }
    }
  }
  
  // Ready to fight
  fs->start();
}

void checkFight( EntityManager &em, CFightSystem *fs){
  // i don' t know how end the game so i check that hero still alive :(
  if ( fs->getDead() != "Richard" ){ 
    CTagEntityMng::TEntityId id = em.getTagMng().getFirstEntityByTag( fs->getDead());
    Entity *e = em.getById( id);
    if ( e){
      em.destroyEntity( id);
    }
  }
}


