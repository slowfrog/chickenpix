#include "Main.h"

// Prepare fight
void prepareFight( EntityManager &em, CFightSystem *fs)
{
  // Check Mode
  if ( em.getName() != FIGHT){
    return;
  }
  // Prepare round
  CTagEntityMng::TEntityId id = CTagEntityMng::get()->getEntityByTag( "HERO");
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
      e = em.getById( (*it));
      if ( e){
        Character *c = e->getComponent<Character>();
        if ( NULL == c)
          return;
        
        // Add fighter
        fs->addFoe( *c);
      }
    }
  }
}


