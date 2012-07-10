#pragma once

#include "System.h"

class Animation: public System {
public:
  Animation(string const &name);
  virtual ~Animation();

  virtual void init   ( EntityManager &);
  virtual void update ( EntityManager &, int);
  virtual void exit   ( EntityManager &);
  
  inline SystemType getType() const { return ANIMATION_TYPE;}
  
  virtual string toString() const;
};
