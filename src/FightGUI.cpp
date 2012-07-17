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

#define LENGHT_TXT          100
#define DELTA_SKILL         65
#define ROUND_LENGTH        85

#define HIGHLIGHT_TEXT_01   "HighLightText01"

// Constrcutor
FightGUI::FightGUI( EntityManager &em)
:mEM(em), mRes(NULL), mAlpha(200){
  mRes = em.getComponent<Resources>();
  assert( mRes); // Can t work without resources
}

// Display all stats for Character
void 
FightGUI::displayAllyStats( Character *c, const bool hero){
  // Display Skill (Hardcoded now)
  addText( "sans_huge", CPColor( 255, 255, 0, 255), START_ALLY_SKILL_X, START_ALLY_SKILL_Y, "A");
  addText( "sans_huge", CPColor( 255, 255, 0, 255), START_ALLY_SKILL_X + DELTA_SKILL, START_ALLY_SKILL_Y, "Q");
  // Display stats
  addText( "sans_norm", CPColor( 200, 200, 128, 200), START_ALLY_NAME_X, START_ALLY_NAME_Y, c->Name());
  addText( "sans_norm", CPColor( 200, 200, 128, 200), START_ALLY_ROUND_X, START_ALLY_ROUND_Y, "Round :");
  displayStats( c, START_ALLY_X, START_ALLY_Y);
  addImage( c->Name(), START_ALLY_IMG_X, START_ALLY_IMG_Y);
  
  // TEST
  addText( "sans_norm", CPColor( 200, 200, 128, 200), START_ALLY_ROUND_X+ROUND_LENGTH, START_ALLY_ROUND_Y, "Attack");
}

void 
FightGUI::displayFoeStats( Character *c){
  // Display Skill (Hardcoded now)
  addText( "sans_huge", CPColor( 255, 255, 0, 200), START_FOE_SKILL_X, START_FOE_SKILL_Y, "-");
  addText( "sans_huge", CPColor( 255, 255, 0, 200), START_FOE_SKILL_X + DELTA_SKILL, START_FOE_SKILL_Y, "-");
  // Display stats
  addText( "sans_norm", CPColor( 200, 200, 128, 200), START_FOE_NAME_X, START_FOE_NAME_Y, c->Name());
  addText( "sans_norm", CPColor( 200, 200, 128, 200), START_FOE_ROUND_X, START_FOE_ROUND_Y, "Round :");
  displayStats( c, START_FOE_X, START_FOE_Y);
  addImage( c->Name(), START_FOE_IMG_X, START_FOE_IMG_Y);
}

void 
FightGUI::displayStats( Character *c, const float startX, const float startY){
  Stats::TMapVariant    vs = c->getStats().get();
  Stats::TMapVariantIt it = vs.begin();
  float inc(0.);
  CPColor color( 255, 255, 0, 200);
  for ( it; it != vs.end(); it++) {
    std::string name;
    getStatsName( (*it).first, name);
    addText( "sans_norm", color, startX, startY+(inc*25.), name);
    CVariant v = (*it).second;
    addText( "sans_norm", color, startX+LENGHT_TXT, startY+(inc*25.), v);
    inc++;
  }
}

void
FightGUI::readyToStart( const std::string& text, int now)
{
  Entity::Id id = mEM.getFirstByTag( HIGHLIGHT_TEXT_01);
  Entity *ent(NULL);
  if ( id != NOT_FOUND){
    mEM.destroyEntity( id);
  }
  // Create new 
  ent = mEM.createEntity();
  mEM.tagEntity( ent, HIGHLIGHT_TEXT_01);
  assert( ent);
  // Properties
  // A revoir pour plus de souplesse avec les properties de la camera, approx de la police aussi
  float x = (800./2.-200) - (text.length()*45)/2.;
  if (x < -400) x = -( 800. - 200.)/2.;
  addText( "sans_big", CPColor( now%255, 128, 0, now%255), x, -200, text);
}

// Prepare stats for display
void 
FightGUI::addText( const std::string &f, const CPColor &c, const float x, const float y, CVariant &v)
{
  // Get Value
  std::ostringstream out;
  out.str("");
  out <<(long)v;
  // display
  addText( f, c, x, y, out.str());
}

// Display stats (adding new entity)
void 
FightGUI::addText(  const std::string   &f, 
                    const CPColor       &c, 
                    float               x, 
                    float               y, 
                    const std::string   &text)
{
  // Create entity
  Entity *ent = mEM.createEntity();
  assert( ent);
  mEM.tagEntity( ent, TAG_STATS);
  
  BVisual *vt = mRes->makeText( text, f, c);
  assert( vt);
  vt->setZOrder( 100);
  
  ent->addComponent( vt);
  ent->addComponent( new Transform( x, y));
}

void FightGUI::addImage( const std::string &name, const float x, const float y){
  // Create entity
  Entity *ent = mEM.createEntity();
  assert( ent);
  
  BVisual *vi = mRes->makeImage( name);
  assert( vi);
  vi->setZOrder( 100);
  ent->addComponent( vi);
  ent->addComponent( new Transform( x, y));
}

// Add text for stats
void 
FightGUI::getStatsName( const long &id, std::string& name)
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