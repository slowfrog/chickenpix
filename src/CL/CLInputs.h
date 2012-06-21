#pragma once
#include "CL.h"
#include "../Inputs.h"

class CLInputs: public Inputs {
private:
  CL_InputDevice *keyboard;
public:
  CLInputs(string const &name, EntityManager &em);
  virtual ~CLInputs();

  virtual bool isKeyDown(Key key) const;
  
  virtual void init();
  virtual void pumpEvents();
  virtual void exit();

  virtual string toString() const;
};
