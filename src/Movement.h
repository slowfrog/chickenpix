#pragma once

#include "System.h"

class Movement: public System {
public:
  Movement(string const &name, EntityManager &em);
  virtual ~Movement();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};
