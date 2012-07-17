#include "TagEntityManager.h"
#include "EntityManager.h"
#include "HandleTransition.h"

// Add entities from source "from" to target "to" (hahaha good naming)
void 
HandleTransition::transit(  EntityManager     &from, 
                            EntityManager     &to, 
                            const std::string &tag
                          )
{
  CTagEntityMng::TCollectionIdEntity vEnt;
  // Search unique (first)
  CTagEntityMng::TEntityId id = CTagEntityMng::get()->getEntityByTag( tag);
  if ( id == NOT_FOUND){
    // Search all (next)
    vEnt = CTagEntityMng::get()->getEntitiesByTag( tag);
  }
  else {
    vEnt.push_back( id);
  }
  
  // Add entities
  if ( !vEnt.empty() ) {
    CTagEntityMng::TCollectionIdEntity::iterator it = vEnt.begin();
    for (it; it != vEnt.end(); it++) {
      // Get entity from source EM 
      Entity *e = from.getById( (*it));
      // Check if exist in target EM, if not, add it
      if ( NULL == to.getById( (*it))){
        to.addEntity( e);
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
  for (it; it != vtag.end(); it++){
    transit( from, to, (*it));
  }
}
