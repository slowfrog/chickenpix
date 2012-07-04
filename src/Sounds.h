#pragma once

#include "System.h"

class EntityManager;

class Sounds: public System {
public:
  Sounds(const string &name, EntityManager &em);
  virtual ~Sounds();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  inline
  virtual SystemType getType() const {
    return SOUNDS_TYPE;
  }

  virtual string toString() const;
};
