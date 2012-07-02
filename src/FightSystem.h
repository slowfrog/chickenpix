#pragma once

#include <list>
#include <queue>
#include <string>

#include "EntityManager.h"
#include "System.h"
#include "Stats.h"

// Forward
class CFightSystem; 

// Types
typedef Character  CFighter;

/**
 State for fight round
 */
/****************************************************************/
/* CRoundInit : interface                                       */
/****************************************************************/
class IRoundState {
public:
    virtual IRoundState* addFighter     ( CFightSystem&, const CFighter&, const bool)   { return 0;}
    virtual IRoundState* start          ( CFightSystem&) { return 0; }
    virtual IRoundState* popFighter     ( CFightSystem&) { return 0; }
    virtual IRoundState* chooseTarget   ( CFightSystem&) { return 0; }
    virtual IRoundState* chooseSkill    ( CFightSystem&) { return 0; }
    virtual IRoundState* doFight        ( CFightSystem&) { return 0; }
    virtual IRoundState* next           ( CFightSystem&) { return 0; }

    virtual std::string toString() =0;
};

/****************************************************************/
/* CRoundInit                                                   */
/****************************************************************/
class CRoundInit : public IRoundState {
public:
  virtual IRoundState* addFighter ( CFightSystem&, const CFighter&, const bool);
  virtual IRoundState* start      ( CFightSystem&);
  virtual std::string toString() {static std::string ret("CRoundInit"); return ret;}
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
    virtual IRoundState* next( CFightSystem&);

    virtual std::string toString() {return "CRoundFight";}
};

/****************************************************************/
/* CRoundFinish                                                 */
/****************************************************************/
class CRoundFinish : public IRoundState {
public:
    virtual std::string toString() {return "CRoundFinish";}
};

/****************************************************************/
/* CFightEngine                                                 */
/****************************************************************/
class CFightSystem : public System {
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
  CFightSystem( const std::string&, EntityManager&);
  virtual	~CFightSystem();
	
  // API
  void addFoe (const CFighter&);
  void addAlly(const CFighter&);
  void processRounds();
  
  // System API
  void init();
  void update(int);
  void exit();
  
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
  //
  bool isDeadDef();  
  
private:
  static IRoundState              *curState;
  std::list<CFighter>             vFoe;
  std::list<CFighter>             vAlly;
  std::queue<CFighter>            vDead;
  std::queue<CFighter>            qAtt;
  std::queue<CFighter>            qAttBck;
  std::queue<CFighter>            qDef;
  bool                            endOfFight;
  
  // State
  TeState                         curFg;
};
