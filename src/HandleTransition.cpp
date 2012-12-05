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
 
#include "TagEntityManager.h"
#include "EntityManager.h"
#include "HandleTransition.h"
#include "Stats.h"

// Add entities from source "from" to target "to" (hahaha good naming)
void 
HandleTransition::transit(  EntityManager     &from, 
                            EntityManager     &to, 
                            const std::string &tag,
                            const bool        unique
                          )
{
  CTagEntityMng::TCollectionIdEntity vEnt;
  // Search unique (first)
  CTagEntityMng::TEntityId id = from.getTagMng().getFirstEntityByTag( tag);
  if ( id == NOT_FOUND){
    // Search all (next)
    vEnt = from.getTagMng().getEntitiesByTag( tag);
  }
  else {
    vEnt.push_back( id);
  }
  
  // Add entities
  if ( !vEnt.empty() ) {
    CTagEntityMng::TCollectionIdEntity::iterator it = vEnt.begin();
    for (; it != vEnt.end(); it++) {
      // Get entity from source EM 
      Entity *e = from.getById( (*it));
      // Check entity
      if ( e ){
        Entity *new_e = to.createEntity();
        to.tagEntity( new_e, tag, unique);
        Character *c = e->getComponent<Character>();
        if ( c) {
          //new_e->removeComponent( Character::TYPE);
          new_e->addComponent( new Character( *c));
        }
      }
    }
  }
}

// Same as previous but with list of tag
void 
HandleTransition::transit(  EntityManager         &from, 
                            EntityManager         &to, 
                            const TTagCollection  &vtag
                          )
{
  // Loop on tag list
  TTagCollection::const_iterator it = vtag.begin();
  for (; it != vtag.end(); it++){
    transit( from, to, (*it));
  }
}

void 
HandleTransition::copyComponent( const Entity *src, Entity * dst){
  Component *c = src->getComponent<Character>();
  if ( c){
  dst->addComponent( c);
  }
}
