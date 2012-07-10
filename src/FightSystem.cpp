#include <sstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "log.h"
#include "FightSystem.h"

/****************************************************************/
/* CRoundInit                                                   */
/****************************************************************/
IRoundState* 
CRoundInit::addFighter( CFightSystem& fe, const CFighter& f, const bool ally){
    fe.add( f, ally);
    return this;
}

IRoundState*
CRoundInit::start( CFightSystem& fe){
    fe.startRound();
    return new CRoundPrepare;
}

/****************************************************************/
/* CRoundPrepare                                                */
/****************************************************************/
IRoundState* 
CRoundPrepare::popFighter( CFightSystem& fe){
    fe.curFighter();
    return this;
}

IRoundState* 
CRoundPrepare::chooseTarget( CFightSystem& fe){
    fe.curTarget();
    return this;
}

IRoundState* 
CRoundPrepare::chooseSkill( CFightSystem& fe){
    fe.curSkill();
    return this;  
}

IRoundState* 
CRoundPrepare::doFight( CFightSystem& fe){
    fe.curFight();
    return new CRoundFight;
}

/****************************************************************/
/* CRoundFight                                                  */
/****************************************************************/
IRoundState* 
CRoundFight::next( CFightSystem& fe){
    fe.nextRound();
    return new CRoundPrepare;
}

/****************************************************************/
/* CFightEngine: Round fight management                         */
/****************************************************************/
// Init static
IRoundState *CFightSystem::curState = NULL;

// Sort by initiative
bool 
sortByInitiative(const CFighter& a, const CFighter& b){
  return b.get(INITIATIVE) < a.get(INITIATIVE);
}

/**
 */
CFightSystem::CFightSystem( const std::string &name, EntityManager &em): System( name), endOfFight(false){
	/*curState = new CRoundInit;
	if ( !curState ) throw "[CFightEngine] failed.";
    CDice<>::init();*/
}

/**
 */
CFightSystem::~CFightSystem(){
	if ( curState){
		delete curState;
	}
	curState = NULL;
}

/**
 */
void 
CFightSystem::setState(IRoundState* s){
	if ( s && curState && curState != s){
		delete curState;
		curState = s;
	}
}

/**
 */
void 
CFightSystem::addFoe( const CFighter& f){
  setState( curState->addFighter( *this, f, false));
}

/**
 */
void 
CFightSystem::addAlly( const CFighter& f){
  setState( curState->addFighter( *this, f, true));
}

/**
 */
void 
CFightSystem::processRounds(){
	// Start round
	setState( curState->start( *this));
	// main loop
	while ( !fightOver() ) {
        setState( curState->popFighter   ( *this));		// Update fighter
        setState( curState->chooseTarget ( *this));	  // Choose enemy if more than one
        setState( curState->chooseSkill  ( *this));	  // Choose skill/weapon/...
        //
        setState( curState->doFight      ( *this));		// appliquer les lance de dés en fonction de caracteristique arme + perso applique les degats, historise les coups
        setState( curState->next         ( *this));	  // next round
    
        // Debug
        LOG2DBG <<"Next ...\n";
	}
}

bool 
CFightSystem::add(const CFighter& f, const bool ally){
  if ( ally){
    vAlly.push_back( f);
  }
  else{
    vFoe.push_back( f);
  }
  return true;
}

/**
*/
bool 
CFightSystem::startRound(){
  // sort fighters by initiative
  vFoe.sort ( sortByInitiative);
  vAlly.sort( sortByInitiative);
  
  long sA(0), sF(0);
  std::for_each( vAlly.begin(), vAlly.end(), sumInitiative( sA));
  std::for_each( vFoe.begin(),  vFoe.end(),  sumInitiative( sF));
  
  // Set first fighter
  if ( sA/vAlly.size() > sF/vFoe.size() ){
    curFg = STATE_ALLY_FOE;
    std::for_each( vAlly.begin(), vAlly.end(), FillStack( qAtt));
    std::for_each( vFoe.begin(),  vFoe.end(),  FillStack( qDef));
  }
  else{
    curFg = STATE_FOE_ALLY;
    std::for_each( vAlly.begin(), vAlly.end(), FillStack( qDef));
    std::for_each( vFoe.begin(),  vFoe.end(),  FillStack( qAtt));
  }
  return true;
}

bool
CFightSystem::curFighter(){
  // Default behavior
  qAtt.front();
  LOG2DBG << qAtt.front().Name()<< " attacks\n";
  LOG2DBG << qAtt.front().toString()<<"\n";
  // Update IHM with skill, stats of current fighter
  // Maybe : choose fighter
  return true;
}

bool 
CFightSystem::curTarget(){
  qDef.front();
  LOG2DBG << qDef.front().Name()<< " defends\n";
  LOG2DBG << qDef.front().toString()<<"\n";
  // Select target with GUI
  // ok
  return true;
}

bool 
CFightSystem::curSkill(){
  // Selection de l attaque pour le tour en cours
  // Peut fuire
  return true;
}

bool 
CFightSystem::curFight(){
  // Get CA  
  long ca = CDice<8>::rolled(); // die 6 faces
  LOG2DBG << "CA : "<< ca << "\n";
  
  if ( qDef.front().get( ARMOR_CLASS) < ca ) {
    // Get damage    
    long dmg = (long)qAtt.front().get( DAMAGE) + CDice<20>::rolled(); // die 20 faces
    // apply damage on health point
    change(qDef.front(), HEALTH, CVariant( dmg), minusVar);
    LOG2DBG << "dmg : "<< dmg << "\n";
    LOG2DBG << qDef.front().toString()<<"\n";
  }
  return true;
}

void 
CFightSystem::nextRound(){
  // Def is dead ?  
  if ( qDef.front().isDead() ){
    LOG2DBG <<qDef.front().Name()<<" is dead\n";
    vDead.push( qDef.front());
    qDef.pop(); // unqueue dead    
    // Check def queue
    if ( qDef.empty() ){
      endOfFight = true;
    }
  }
  
  // Att is empty ?
  qAttBck.push( qAtt.front());
  qAtt.pop(); // unqueue current
  if ( qAtt.empty()) {
    // Switch queue
    std::swap(qDef, qAttBck);
    std::swap(qAtt, qAttBck);
    if ( curFg == STATE_ALLY_FOE){
      curFg = STATE_FOE_ALLY;
    }
    else {
      curFg = STATE_ALLY_FOE;
    }
  }
  else { 
    // Next att, GUI access ?
    qAtt.front();
  }
}

/*
 Display Information
*/
std::string 
CFightSystem::toString(){
  std::ostringstream out;
  out<<std::endl<<"Current state: ["<<curState->toString()<<"]"<<std::endl;
  
  out<<"Foe(s)"<<std::endl;
  std::list<CFighter>::const_iterator cit = vFoe.begin();
  while (cit != vFoe.end()) {
    out<<"\t"<<(*cit).toString();
    cit++;
  }
  
  out<<"Ally(ies)"<<std::endl;
  cit = vAlly.begin();
  while (cit != vAlly.end()) {
    out<<"\t"<<(*cit).toString();
    cit++;
  }
  return out.str();
}

/*
 System API
 */
// Init
void CFightSystem::init(){
  curState = new CRoundInit;
	if ( !curState ) throw "[CFightEngine] failed.";
  CDice<>::init();
}

// Update
void CFightSystem::update(int){
}

// Exit
void CFightSystem::exit(){
}
