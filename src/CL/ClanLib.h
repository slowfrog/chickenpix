#pragma once
#include "CL.h"
#include "../System.h"

class ClanLib: public System {
private:
  CL_SetupCore *setupCore;
  CL_SetupDisplay *setupDisplay;
  CL_SetupSWRender *setupSWRender;
  
public:
  ClanLib(string const &name, EntityManager &em);
  virtual ~ClanLib();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};
