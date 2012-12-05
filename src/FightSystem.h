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
 
#pragma once

#include <list>
#include <queue>
#include <string>

#include "FightGUI.h"
#include "EntityManager.h"
#include "System.h"
#include "Stats.h"

// Constant(s)
#define FS_NOTIFIER_QUIT        "Quit"
#define FS_NOTIFIER_SKILL       "SkillAttack"

// Forward
class CFightSystem; 

// Types
typedef Character  CFighter;

// Callbacks def
void NotifyQuit     ( System*);
void NotifyAttack   ( System*);

/**
 States for fight round
 */
/****************************************************************/
/* CRoundInit : interface                                       */
/****************************************************************/
class IRoundState {
public:
  virtual IRoundState* start          ( CFightSystem&) { return 0; }
  virtual IRoundState* addFighter     ( CFightSystem&, const CFighter&, const bool)   { return 0;}
  virtual IRoundState* popFighter     ( CFightSystem&) { return 0; }
  virtual IRoundState* chooseTarget   ( CFightSystem&) { return 0; }
  virtual IRoundState* chooseSkill    ( CFightSystem&) { return 0; }
  virtual IRoundState* doFight        ( CFightSystem&) { return 0; }
  virtual IRoundState* next           ( CFightSystem&) { return 0; }
  virtual IRoundState* finish         ( CFightSystem&) { return 0; }
  virtual IRoundState* quit           ( CFightSystem&);
  
  virtual void update ( EntityManager &, CFightSystem&, int);
  virtual void init   ( EntityManager &){}
  virtual void exit   ( EntityManager &){}
  
  virtual std::string toString() =0;
};

/****************************************************************/
/* CRoundInit                                                   */
/****************************************************************/
class CRoundInit : public IRoundState {
public:
  virtual IRoundState* addFighter ( CFightSystem&, const CFighter&, const bool);
  virtual IRoundState* start      ( CFightSystem&);
  
  //virtual void update ( EntityManager &, CFightSystem&, int);
  virtual std::string toString() { return "CRoundInit";}
};

/****************************************************************/
/* CRoundPrepare                                                */
/****************************************************************/
class CRoundPrepare : public IRoundState {
public:
  virtual IRoundState* popFighter     ( CFightSystem&);
  virtual IRoundState* chooseTarget   ( CFightSystem&);
  virtual IRoundState* chooseSkill    ( CFightSystem&);
  virtual IRoundState* doFight        ( CFightSystem&);

  virtual std::string toString() {return "CRoundPrepare";}
};

/****************************************************************/
/* CRoundFight                                                  */
/****************************************************************/
class CRoundFight : public IRoundState {
public:    
  virtual IRoundState* next   ( CFightSystem&);
  virtual IRoundState* finish ( CFightSystem&);

  virtual std::string toString() {return "CRoundFight";}
};

/****************************************************************/
/* CRoundFinish                                                 */
/****************************************************************/
class CRoundFinish : public IRoundState {
public:
  virtual void update ( EntityManager &, CFightSystem&, int);
  
  virtual std::string toString() {return "CRoundFinish";}
};

/****************************************************************/
/* CFightEngine                                                 */
/****************************************************************/
class CFightSystem : public System {
  friend class IRoundState;
  friend class CRoundInit;
  friend class CRoundPrepare;
  friend class CRoundFight;
  friend class CRoundFinish;

  // State
  typedef enum {
    STATE_ALLY_FOE  =1,
    STATE_FOE_ALLY 
  } TeState;
  
  typedef std::list<CFighter>                 TCollectionFighter;
  typedef TCollectionFighter::iterator        TCollectionFighterIt;
  typedef TCollectionFighter::const_iterator  TCollectionFighterCIt;
  
  typedef std::queue<CFighter>                TQueueFighter;
  
public:
  // Constructor/destructor
  CFightSystem( const std::string&);
  virtual	~CFightSystem();
  
  // System API
  inline SystemType getType() const { return FIGHT_TYPE;}
  void init   ( EntityManager &);
  void update ( EntityManager &, int);
  void exit   ( EntityManager &);
	
  // API
  void start  ();
  void addFoe ( const CFighter&);
  void addAlly( const CFighter&);
  void attack ();
  void next   ();
  void quit   ();
  
  bool checkExit( EntityManager &);
  void reset();
  
  // Transition
  void updateStats( EntityManager &, const std::string &tag, const bool ally= false);
  
  inline const std::string& getDead() const { return mDead;}
  
  // Display GUI
  void refresh( EntityManager&, int);
  
  // Display info
  std::string toString();
  
protected:
  // Usefull functor(s) works with std::for_each
  struct FillStack {
    FillStack(std::queue<CFighter>& f):_f(f){}
    void operator()(CFighter& f){ _f.push( f);}

    std::queue<CFighter>& _f;
  };
  
  struct sumInitiative {
    sumInitiative(long& n):_sum(n){}
    void operator()(CFighter& f){ _sum += (long)f.get(INITIATIVE);}
    
    long& _sum;
  };
	
protected:
  inline UIManager *getUI() { return mUI;}
  // Set current state
  void setState(IRoundState*);
  // Check if fight must ended
  inline bool fightOver() { return endOfFight;}
  // Action from states
  bool startRound();
  bool add(const CFighter&, const bool);
  bool curFighter();
  bool curTarget();
  bool curSkill();
  bool curFight();
  void nextRound();
  void finishRound();
  //
  bool isDeadDef();  
  
private:
  UIManager           *mUI;
  // Fight management
  static IRoundState  *curState;
  TCollectionFighter  vFoe;
  TCollectionFighter  vAlly;
  TQueueFighter       vDead;
  TQueueFighter       qAtt;
  TQueueFighter       qAttBck;
  TQueueFighter       qDef;
  bool                endOfFight;
  bool                exitAsked;
  // State
  TeState             curFg;
  // Dead ?
  std::string         mDead;
};
