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


