#include <math.h>

#include "EntityManager.h"
#include "TagEntityManager.h"
#include "Transform.h"
#include "Stats.h"
#include "Resources.h"
#include "FightGUI.h"

// Constants
#define START_ALLY_X        -330
#define START_ALLY_Y        -140

#define START_ALLY_NAME_X   -370
#define START_ALLY_NAME_Y   -282

#define START_ALLY_SKILL_X  -372
#define START_ALLY_SKILL_Y  6

#define START_ALLY_IMG_X    -346
#define START_ALLY_IMG_Y    -205

#define START_ALLY_ROUND_X  -295
#define START_ALLY_ROUND_Y  -245

#define START_ALLY_INFO_X   -295
#define START_ALLY_INFO_Y   -200

#define START_FOE_X         -30
#define START_FOE_Y         START_ALLY_Y

#define START_FOE_NAME_X    -70
#define START_FOE_NAME_Y    START_ALLY_NAME_Y

#define START_FOE_SKILL_X   -78
#define START_FOE_SKILL_Y   START_ALLY_SKILL_Y

#define START_FOE_IMG_X     146
#define START_FOE_IMG_Y     START_ALLY_IMG_Y

#define START_FOE_ROUND_X  -80
#define START_FOE_ROUND_Y  START_ALLY_ROUND_Y

#define START_FOE_INFO_X   -80
#define START_FOE_INFO_Y   START_ALLY_INFO_Y

#define START_CONSOLE_X     -380
#define START_CONSOLE_Y     105

#define LENGHT_TXT          100
#define DELTA_SKILL         65
#define ROUND_LENGTH        85

//
#define SKILL_ATTACK        "SkillAttack"
#define SKILL_QUIT          "SkillQuit"

// 
#define LEFT_PANEL_TAG      "leftPanel"
#define RIGHT_PANEL_TAG     "RightPanel"
#define CONSOLE             "Console"

#define FONT_S              "sans_small"
#define FONT_N              "sans_norm"
#define FONT_B              "sans_big"
#define FONT_H              "sans_huge"

#ifndef PI
#define PI  3.14159
#endif

/**************************************************************/
/* GUIEngine                                                  */
/**************************************************************/
void 
UIEngine::setResources( Resources *r){
  mRes = r;
}

void 
UIEngine::buildText(Entity             *e, 
                    const std::string  &t, 
                    const std::string  &f,
                    const CPColor      &c,
                    const float        x, 
                    const float        y
                    )
{
  BVisual *vt = mRes->makeText( t, f, c);
  assert( vt);
  vt->setZOrder( 100);
  e->addComponent( vt);
  e->addComponent( new Transform( x, y));
}

void 
UIEngine::buildImg (Entity             *e, 
                    const std::string  &i, 
                    const float        x, 
                    const float        y
                    )
{
  BVisual *vi = mRes->makeImage( i);
  assert( vi);
  vi->setZOrder( 100);
  e->addComponent( vi);
  e->addComponent( new Transform( x, y));
}

/**************************************************************/
/* IUIPart                                                    */
/**************************************************************/
// 
int
IUIPart::getAlpha( const int def){
  if ( isTimeShift() ){
    mTheta += 20;
    return 255*fabs(cos( (mTheta*2.f*PI)/360.f));
  }
  return def;
}

// Resources
void 
IUIPart::buildResource( Entity *e, UIEngine *eng, const sInfoRs &i)
{
  switch( i.sType){
    case eText:
      eng->buildText( e, i.sText, i.sResName, i.sColor, i.sX, i.sY);
      break;
    case eImage:
      eng->buildImg( e, i.sResName, i.sX, i.sY);
      break;
    default:
      break;
  }
}

/**************************************************************/
/* UIStats                                                    */
/**************************************************************/
// Add label for stats
void 
UIStats::getStatsName( const long &id, std::string& name)
{
  switch( id){
    case HEALTH:
      name = TAG_HEALTH;
      break;
    case DAMAGE:
      name = TAG_DAMAGE;
      break;
    case ARMOR_CLASS:
      name = TAG_ARMOR;
      break;
    case INITIATIVE:
      name = TAG_INITATIVE;
      break;
    default:
      name="xxx";
      break;
  }
}

// Prepare stats to display
void 
UIStats::addStatsFighters( const Character *c, const bool isAlly){
  Stats::TMapVariant    vs = c->getStats().get();
  Stats::TMapVariantIt  it = vs.begin();
  float                 inc(0.);
  std::ostringstream    out;
  std::string           name;
  // Loop on stats
  for ( it; it != vs.end(); it++) {
    out.str("");
    getStatsName( (*it).first, name);
    mStaticRes.push_back( sInfoRs( name, FONT_N, 
                                  (isAlly)?START_ALLY_X:START_FOE_X, 
                                  ((isAlly)?START_ALLY_Y:START_FOE_Y)+(inc*25.), 
                                  HIGH_YELLOW));
    long v = (long)(*it).second;
    out << v;
    mDynamicRes.insert( std::make_pair(c->Name() + name, 
                                       sInfoRs(out.str(), FONT_N, 
                                               ((isAlly)?START_ALLY_X:START_FOE_X)+LENGHT_TXT, 
                                               ((isAlly)?START_ALLY_Y:START_FOE_Y)+(inc*25.), 
                                               HIGH_YELLOW)
                                       )
                       );
    inc++;
  }
  // Round text
  mStaticRes.push_back( sInfoRs( "Round :", FONT_N, 
                                (isAlly)?START_ALLY_ROUND_X:START_FOE_ROUND_X, 
                                (isAlly)?START_ALLY_ROUND_Y:START_FOE_ROUND_Y, 
                                HIGH_YELLOW));
  // Name
  mDynamicRes.insert( std::make_pair(TAG_NAME + c->Name(), 
                                     sInfoRs(c->Name(), FONT_N, 
                                             (isAlly)?START_ALLY_NAME_X:START_FOE_NAME_X, 
                                             (isAlly)?START_ALLY_NAME_Y:START_FOE_NAME_Y, 
                                             LIGHT_BROWN)
                                     )
                     );
  // Image
  mDynamicRes.insert( std::make_pair(TAG_IMG + c->Name(), 
                                     sInfoRs(c->Name(), 
                                             (isAlly)?START_ALLY_IMG_X:START_FOE_IMG_X, 
                                             (isAlly)?START_ALLY_IMG_Y:START_FOE_IMG_Y)
                                     )
                     );  
}

void
UIStats::updateStats( const Character *c){
  Stats::TMapVariant    vs = c->getStats().get();
  Stats::TMapVariantIt  it = vs.begin();
  std::ostringstream    out;
  std::string           name;
  long                  value(0L);
  // Loop on stats
  for ( it; it != vs.end(); it++) {
    getStatsName( (*it).first, name);
    TMapTagRes::iterator itf = mDynamicRes.find( c->Name() + name);
    if (itf != mDynamicRes.end()){
      value = (long)(*it).second;
      out << ((value<0)?0:value);
      itf->second.sText = out.str();
      out.str("");
    }
  }
}

void 
UIStats::updateRole( const std::string &name, const bool ally){
  TMapTagRes::iterator it = mDynamicRes.find( name);
  sInfoRs info(name, FONT_N, 
               (ally)?START_ALLY_ROUND_X+ROUND_LENGTH:START_FOE_ROUND_X+ROUND_LENGTH, 
               (ally)?START_ALLY_ROUND_Y:START_FOE_ROUND_Y, 
               LIGHT_RED);
  if ( it != mDynamicRes.end()) {
    it->second = info;
  }
  else {
    mDynamicRes.insert( std::make_pair( name, info));
  }  
}

// Info
void 
UIStats::infoStats( const std::string& i, const bool left, CPColor c, const bool highlight){
  // Info 
  std::string panel = (left)?LEFT_PANEL_TAG:RIGHT_PANEL_TAG;
  TMapTagRes::iterator it = mDynamicRes.find( panel);
  sInfoRs info( i, FONT_N, 
               (left)?START_ALLY_INFO_X:START_FOE_INFO_X, 
               (left)?START_ALLY_INFO_Y:START_FOE_INFO_Y, 
               c, highlight);
  if ( it != mDynamicRes.end()) {
    it->second = info;
  }
  else {
    mDynamicRes.insert( std::make_pair( panel, info));
  }
}

// Display fixed entities
void 
UIStats::refreshFixedPart ( EntityManager &em, UIEngine *eng, int now){
  TVecRes::iterator it = mStaticRes.begin();
  for (it; it != mStaticRes.end(); it++){
    Entity *e = em.createEntity();
    assert( e);
    em.tagEntity( e, TAG_FIXED);
    buildResource( e, eng, (*it));
  }
}

// Display dynamic entities
void 
UIStats::refreshPart( EntityManager &em, UIEngine *eng, int now){
  // Parse objects
  TMapTagRes::iterator it = mDynamicRes.begin();
  while ( it != mDynamicRes.end()) {
    // Check tag
    Entity::Id id = em.getFirstByTag( (*it).first);
    if ( id != NOT_FOUND) {
      em.destroyEntity( id);
    }
    // Highlight 
    if ( (*it).second.sHighLight) {
      (*it).second.sColor.a = getAlpha( (*it).second.sColor.a);
    }
    // Create new entity
    Entity *e = em.createEntity();
    assert( e);
    em.tagEntity( e, (*it).first, true);
    buildResource( e, eng, (*it).second);
    it++; // Next
  }
}

/**************************************************************/
/* GUIConsole                                                 */
/**************************************************************/
// New line
void 
UIConsole::newLine( const std::string &txt){
  mLastInserted = mCur = mVLines.size();
  mVLines.push_back( txt);
}

//
void 
UIConsole::buildDisplayedLine(){
  TVecTxt::reverse_iterator it = mVLines.rbegin();
  mDynamicRes.clear();
  TPos    nb( 0);
  CPColor c ( 255, 255, 255, 255);
  while ( it != mVLines.rend() && nb < 16) {
    if ( nb == 0){
      c.r = c.g = c.b = 255;
    }
    else {
      c.r = c.g = c.b = 200;
    }

    //addText
    sInfoRs info((*it), FONT_S, 
                 START_CONSOLE_X, 
                 START_CONSOLE_Y + ( nb * 10), 
                 c);
    std::ostringstream    out;
    out << CONSOLE <<nb;
    mDynamicRes.insert( mDynamicRes.begin(), std::make_pair( out.str(), info));
    nb++;
    it++;
  }
}

// Add fixed entity to display
void 
UIConsole::refreshFixedPart( EntityManager &em, UIEngine *eng, int now){
}

// Add dynamic entity to display
void 
UIConsole::refreshPart( EntityManager &em, UIEngine *eng, int now){
  buildDisplayedLine();
  // Parse objects
  TMapTagRes::iterator it = mDynamicRes.begin();
  while ( it != mDynamicRes.end()) {
    // Check tag
    Entity::Id id = em.getFirstByTag( (*it).first);
    if ( id != NOT_FOUND) {
      em.destroyEntity( id);
    }
    // Create new entity
    Entity *e = em.createEntity();
    assert( e);
    em.tagEntity( e, (*it).first, true);
    buildResource( e, eng, (*it).second);
    it++; // Next
  }
}

/**************************************************************/
/* UIManager                                                  */
/**************************************************************/
// Constructor
UIManager::UIManager( Resources *res)
:mRes( res) {
  assert( res);
  mUIEngine.setResources( res);
}

// API
void 
UIManager::refreshAll( EntityManager &em, int now){
  mGUIStats.refresh   ( em, &mUIEngine, now);
  mGUIConsole.refresh ( em, &mUIEngine, now);
}

void 
UIManager::addStats( const Character *c, const bool ally){
  mGUIStats.addStatsFighters( c, ally);
}

void 
UIManager::updateStats( Character *c, const bool ally){
  mGUIStats.updateStats( c);
}

void 
UIManager::displayRole( const std::string &tag, const bool isAlly){
  mGUIStats.updateRole( tag, isAlly);
}

void 
UIManager::displayInfo( const std::string &info, const bool left, CPColor c, const int delta){
  mGUIStats.infoStats( info, left, c, delta);
}

void 
UIManager::consoleInfo( const std::string &line){
  mGUIConsole.newLine( line);
}

