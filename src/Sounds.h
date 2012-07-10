#pragma once

#include "System.h"

class EntityManager;

class Sounds: public System {
public:
  Sounds(const string &name);
  virtual ~Sounds();

  virtual void init   ( EntityManager &em);
  virtual void update ( EntityManager &em, int now);
  virtual void exit   ( EntityManager &em);

  inline
  virtual SystemType getType() const {
    return SOUNDS_TYPE;
  }

  virtual string toString() const;
};
