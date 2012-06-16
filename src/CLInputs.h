#pragma once

#include <ClanLib/display.h>
#include "System.h"

class CLInputs: public System {
private:
  bool exitRequested;
  CL_InputDevice *keyboard;
public:
  CLInputs(string const &name, EntityManager &em);
  virtual ~CLInputs();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  bool isExitRequested() const;
  
  virtual string toString() const;
};
