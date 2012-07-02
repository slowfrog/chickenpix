#pragma once
#include "CL.h"
#include "../Inputs.h"
#include "CLInputState.h"

class CLInputs: public Inputs {
private:
  CL_InputDevice *keyboard_;
  CL_InputDevice *mouse_;
  CLInputState *state_;
public:
  CLInputs(string const &name, EntityManager &em);
  virtual ~CLInputs();

  virtual void init();
  virtual void pumpEvents();
  virtual void exit();
  virtual InputState const *getInputState() const;
  
  virtual string toString() const;
};
