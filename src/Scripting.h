#pragma once

#include "System.h"

class Scripting: public System {
public:
  Scripting(string const &name, EntityManager &em);
  virtual ~Scripting();

  virtual void init();
  virtual void update(int now);
  virtual void exit();
  virtual string toString() const;
};
