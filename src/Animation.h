#pragma once

#include "System.h"

class Animation: public System {
public:
  Animation(string const &name, EntityManager &em);
  virtual ~Animation();

  virtual void init();
  virtual void update(int);
  virtual void exit();
  
  virtual string toString() const;
};
