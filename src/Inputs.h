#pragma once

#include "System.h"

class InputState;

class Inputs: public System {
protected:
  bool exitRequested_;
  // Game state
  bool  fightMode_;
public:
  Inputs(string const &name);
  virtual ~Inputs();

  virtual void init   ( EntityManager &em);
  virtual void update ( EntityManager &em, int now);
  virtual void exit   ( EntityManager &em) = 0;
  
  virtual void pumpEvents() = 0;
  virtual InputState const *getInputState() const = 0;

  bool isExitRequested() const;
  
  inline SystemType getType() const { return INPUTS_TYPE;}
  
  virtual string toString() const;

private:
  // Round fight
  void initiateFight(int now);
};
