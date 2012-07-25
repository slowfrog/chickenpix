#include <sstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "log.h"
#include "Resources.h"
#include "Transform.h"
#include "Stats.h"
#include "TagEntityManager.h"
#include "FightGUI.h"
#include "FightSystem.h"

/****************************************************************/
/* Callbacks                                                    */
/****************************************************************/
// 'A' for attack
void NotifyAttack( System *arg){
  CFightSystem *fs = (CFightSystem*) arg;
  if ( fs){
    fs->next();
  }
}

/****************************************************************/
/* IRoundState                                                  */
/****************************************************************/
void 
IRoundState::update( EntityManager &em, CFightSystem &fs, int now){
  // Update or draw something
  fs.refresh( em, now);
}

/****************************************************************/
/* CRoundInit                                                   */
/****************************************************************/
IRoundState* 
CRoundInit::addFighter( CFightSystem &fs, const CFighter &f, const bool ally){
    fs.add( f, ally);
    return this;
}

IRoundState*
CRoundInit::start( CFightSystem &fs){
  fs.startRound();
  fs.attack();
  return new CRoundPrepare;
}

/****************************************************************/
/* CRoundPrepare                                                */
/****************************************************************/
IRoundState* 
CRoundPrepare::popFighter( CFightSystem &fs){
    fs.curFighter();
    return this;
}

IRoundState* 
CRoundPrepare::chooseTarget( CFightSystem &fs){
    fs.curTarget();
    return this;
}

IRoundState* 
CRoundPrepare::chooseSkill( CFightSystem &fs){
    fs.curSkill();
    return this;  
}

IRoundState* 
CRoundPrepare::doFight( CFightSystem &fs){
    fs.curFight();
    return new CRoundFight;
}

/****************************************************************/
/* CRoundFight                                                  */
/****************************************************************/
IRoundState* 
CRoundFight::next( CFightSystem &fs){
    fs.nextRound();
    return this;
}

IRoundState* 
CRoundFight::finish( CFightSystem &fs){
  if ( fs.fightOver()){
    fs.finishRound();
    return new CRoundFinish;
  }
  else {
    return new CRoundPrepare;
  }
}

/****************************************************************/
/* CRoundFinish                                                  */
/****************************************************************/
void 
CRoundFinish::update( EntityManager &em, CFightSystem &fs, int now){
  // Update fighters
  fs.updateFighters( em);
  // Update or draw something
  IRoundState::update( em, fs, now);
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

// Constructor
CFightSystem::CFightSystem( const std::string &name)
: System( name), mUI( NULL), endOfFight( false), mDead(""){
  // Register event
  NotificationCenter::get()->registerNotification( this, FS_NOTIFIER_SKILL, NotifyAttack);
}

// Destructor
CFightSystem::~CFightSystem(){
	if ( curState){
		delete curState;
	}
  if ( mUI) {
    delete mUI;
  }
  
  mUI      = NULL;
	curState = NULL;
  
  NotificationCenter::get()->unregisterNotification( this, FS_NOTIFIER_SKILL);
}

// State accessor
void 
CFightSystem::setState(IRoundState* s){
	if ( s && curState && curState != s){
		delete curState;
		curState = s;
	}
}

// Add fighter ally/Foe
void 
CFightSystem::addFoe( const CFighter& f){
  setState( curState->addFighter( *this, f, false));
}

void 
CFightSystem::addAlly( const CFighter& f){
  setState( curState->addFighter( *this, f, true));
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

void
CFightSystem::reset(){
  vAlly.clear();
  vFoe.clear();
  endOfFight  = false; 
  mDead       = "";
}

void CFightSystem::start(){
  // Start round
	setState( curState->start( *this));
}

bool 
CFightSystem::startRound(){
  // sort fighters by initiative
  TCollectionFighter::iterator it = vFoe.begin();
  std::size_t sz = vFoe.size();
  sz = vAlly.size();
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
    getUI()->displayRole( TAG_ATTACKER, true);
    getUI()->displayRole( TAG_DEFENSER, false);
    getUI()->displayInfo( "[A] to continue", true, LIGHT_RED);
  }
  else{
    curFg = STATE_FOE_ALLY;
    std::for_each( vAlly.begin(), vAlly.end(), FillStack( qDef));
    std::for_each( vFoe.begin(),  vFoe.end(),  FillStack( qAtt));
    getUI()->displayRole( TAG_ATTACKER, false);
    getUI()->displayRole( TAG_DEFENSER, true);
  }
  
  // Display stats
  getUI()->addStats( &vAlly.front(), true);
  getUI()->addStats( &vFoe.front(), false);
  
  // ok
  return true;
}

void CFightSystem::attack(){
  // Faire un while pour automatiser les coups de foe
  setState( curState->popFighter   ( *this));		// Update fighter
  setState( curState->chooseTarget ( *this));	  // Choose enemy if more than one
  setState( curState->chooseSkill  ( *this));	  // Choose skill/weapon/...
  if ( curFg == STATE_FOE_ALLY){
    setState( curState->doFight    ( *this));		// Apply fight rules
    setState( curState->next       ( *this));   // Next state
  }
}

bool
CFightSystem::curFighter(){
  // Default behavior
  qAtt.front();
  LOG2DBG << qAtt.front().Name()<< " attacks\n";
  LOG2DBG << qAtt.front().toString()<<"\n";
  // Update IHM with current fighter
  getUI()->displayRole( TAG_ATTACKER, (curFg == STATE_ALLY_FOE));
  return true;
}

bool 
CFightSystem::curTarget(){
  qDef.front();
  LOG2DBG << qDef.front().Name()<< " defends\n";
  LOG2DBG << qDef.front().toString()<<"\n";
  // Select target with GUI
  getUI()->displayRole( TAG_DEFENSER, !(curFg == STATE_ALLY_FOE));
  return true;
}

bool 
CFightSystem::curSkill(){
  // Selection de l attaque pour le tour en cours
  if ( curFg == STATE_ALLY_FOE){
    getUI()->displayInfo( "[A] to continue", true, LIGHT_RED);
  }
  // Peut fuire
  return true;
}

bool 
CFightSystem::curFight(){
  std::ostringstream    out;
  // Get CA  
  long attack = CDice<8>::rolled(); // die 6 faces
  long ca     = (long) qDef.front().get( ARMOR_CLASS);
  LOG2DBG << "CA : "<< ca << "\n";
  out << ">"<< qAtt.front().Name()<< " attacks with ["<< attack << "].";
  
  if ( ca < attack ) {
    // Get damage    
    long dmg = (long)qAtt.front().get( DAMAGE) + CDice<20>::rolled(); // die 20 faces
    // apply damage on health point
    change(qDef.front(), HEALTH, CVariant( dmg), minusVar);
    LOG2DBG << "dmg : "<< dmg << "\n";
    LOG2DBG << qDef.front().toString()<<"\n";
    
    long health = (long) qDef.front().get( HEALTH); 
    out <<"Attack succeed and "<< qDef.front().Name()<< " received "<< dmg<< " point of damage, health is now ["<< ((health<0)?0:health) <<"]";
    getUI()->consoleInfo( out.str());
  }
  else {
    out<<" Attack failed, because "<< qDef.front().Name()<< "'s armor class [" << (long) qDef.front().get( ARMOR_CLASS)<< "] is better than attack !" ;
    getUI()->consoleInfo( out.str());
  }
  
  // Update GUI
  getUI()->updateStats( &qAtt.front(), (curFg == STATE_ALLY_FOE));
  getUI()->updateStats( &qDef.front(), !(curFg == STATE_ALLY_FOE));
  return true;
}

void 
CFightSystem::nextRound(){
  // Def is dead ?  
  if ( qDef.front().isDead() ){
    mDead = qDef.front().Name();
    LOG2DBG <<qDef.front().Name()<<" is dead\n";
    getUI()->displayInfo( qDef.front().Name()+ " is dead", !(curFg == STATE_ALLY_FOE), LIGHT_RED);
    vDead.push( qDef.front());
    qDef.pop(); // unqueue dead    
    // Check def queue
    if ( qDef.empty() ){
      endOfFight = true;
      return;
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
  
  if ( curFg != STATE_ALLY_FOE){
    getUI()->displayInfo( "[A] to continue", true, LIGHT_RED);
  }

}

void CFightSystem::next(){
  // Next round
  setState( curState->doFight ( *this));	// Apply fight rules
  setState( curState->next    ( *this));  // Next round
  setState( curState->finish  ( *this));  // Check end of fight
}

void 
CFightSystem::finishRound(){
  // Display winner
  getUI()->displayInfo( "Winner is " + qAtt.front().Name(), curFg == STATE_ALLY_FOE, LIGHT_BROWN, true);
  getUI()->consoleInfo( "Press [q] to quit Fight mode");
}

void 
CFightSystem::updateFighters( EntityManager &em){
  /*Entity::Id id = em.getFirstByTag( mDead);
  if ( id != NOT_FOUND) {
    Entity *e = em.getById( id);
    em.tagEntity( e, "ToDelete", true);
  }*/
}

/*
 Refresh GUI
 */
void 
CFightSystem::refresh( EntityManager &em, int now){
  // Update all UI parts
  getUI()->refreshAll( em, now);
}

/*
 System API
 */
// Init
void CFightSystem::init( EntityManager &em){
  // Init state
  curState = new CRoundInit;
	if ( !curState ) throw "[CFightEngine] failed.";
  curState->init( em);
  // Init dice
  CDice<>::init();
  // Init UI
  Resources *res = em.getComponent<Resources>();
  assert( res);
  mUI = new UIManager( res);
  assert (mUI);
}

// Update
void CFightSystem::update( EntityManager &em, int now){
  curState->update(em, *this, now);
}

// Exit
void CFightSystem::exit( EntityManager &em){
  curState->exit( em);
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
