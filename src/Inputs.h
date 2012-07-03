#pragma once

#include "System.h"

class InputState;

class Inputs: public System {
protected:
  bool exitRequested_;
  // Game state
  bool  fightMode_;
public:
  Inputs(string const &name, EntityManager &em);
  virtual ~Inputs();

  virtual void init() = 0;
  virtual void pumpEvents() = 0;
  virtual void update(int now);
  virtual void exit() = 0;
  virtual InputState const *getInputState() const = 0;

  bool isExitRequested() const;
  
  inline SystemType getType() const { return INPUTS_TYPE;}
  
  virtual string toString() const;

private:
  // Round fight
  void initiateFight(int now);
};
