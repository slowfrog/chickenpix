#pragma once

// Constants
#define TAG_HERO        "HERO"
#define TAG_FOE         "FoeInFight"

#define TAG_STATS       "Stats"

#define TAG_HEALTH      "Health"
#define TAG_DAMAGE      "Damage"
#define TAG_INITATIVE   "Initiative"
#define TAG_ARMOR       "Armor"

// Forward(s)
class EntityManager;
class Stats;

// Manage visual part of system fight
class FightGUI
{
public:
  // Constructor / Destructor
  FightGUI( EntityManager &em);
  ~FightGUI(){}
  
  // API
  void displayAllyStats ( Character*, const bool = true);
  void displayFoeStats  ( Character*);
  void readyToStart     ( const std::string&, int);
  
protected:
  void displayStats( Character*, const float, const float);
  void getStatsName( const long&, std::string&); 
                    
  void addText ( const std::string&, const CPColor&, const float, const float, const std::string&);
  void addText ( const std::string&, const CPColor&, const float, const float, CVariant&);
  void addImage( const std::string&, const float, const float);
  
private:
  EntityManager &mEM;
  Resources     *mRes;
  int         mAlpha;
};
