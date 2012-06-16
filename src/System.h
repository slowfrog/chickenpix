#pragma once
#include <string>
#include "EntityManager.h"

using namespace std;

class System {
protected:
  string name;
  EntityManager &em;
  
public:
  System(string const &name, EntityManager &em);
  virtual ~System();
  string const &getName() const;

  virtual void init() = 0;
  virtual void update(int) = 0;
  virtual void exit() = 0;
  
  virtual string toString() const;
};
