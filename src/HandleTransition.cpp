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
