#pragma once

#include <list>
#include <queue>
#include <string>
#include "Stats.h"

// Forward
class CFightEngine; 

// Types
typedef CCharacter  CFighter;

/**
 State for fight round
 */
/****************************************************************/
/* CRoundInit : interface                                       */
/****************************************************************/
class IRoundState {
public:
    virtual IRoundState* addFighter     ( CFightEngine&, const CFighter&, const bool)   { return 0;}
    virtual IRoundState* start          ( CFightEngine&) { return 0; }
    virtual IRoundState* popFighter     ( CFightEngine&) { return 0; }
    virtual IRoundState* chooseTarget   ( CFightEngine&) { return 0; }
    virtual IRoundState* chooseSkill    ( CFightEngine&) { return 0; }
    virtual IRoundState* doFight        ( CFightEngine&) { return 0; }
    virtual IRoundState* next           ( CFightEngine&) { return 0; }

    virtual std::string toString() =0;
};

/****************************************************************/
/* CRoundInit                                                   */
/****************************************************************/
class CRoundInit : public IRoundState {
public:
  virtual IRoundState* addFighter ( CFightEngine&, const CFighter&, const bool);
  virtual IRoundState* start      ( CFightEngine&);
  virtual std::string toString() {static std::string ret("CRoundInit"); return ret;}
};

/****************************************************************/
/* CRoundPrepare                                                */
/****************************************************************/
class CRoundPrepare : public IRoundState {
public:
    virtual IRoundState* popFighter     ( CFightEngine&);
    virtual IRoundState* chooseTarget   ( CFightEngine&);
    virtual IRoundState* chooseSkill    ( CFightEngine&);
    virtual IRoundState* doFight        ( CFightEngine&);

    virtual std::string toString() {return "CRoundPrepare";}
};

/****************************************************************/
/* CRoundFight                                                  */
/****************************************************************/
class CRoundFight : public IRoundState {
public:    
    virtual IRoundState* next( CFightEngine&);

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
class CFightEngine /*: public system*/{
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
  CFightEngine();
  virtual	~CFightEngine();
	
  // API
  void addFoe (const CFighter&);
  void addAlly(const CFighter&);
  void processRounds();
  
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
  // Copy not allowed
  CFightEngine(const CFightEngine&) {throw;}	
	
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
