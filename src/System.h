#pragma once
#include <string>
#include "SystemRegistry.h"
#include "EntityManager.h"

using namespace std;

/*
 System interface
*/
class System {
protected:
  string _name;
  EntityManager &_em;
  
public:
  System(string const &name, EntityManager &em);
  virtual ~System();
  string const &getName() const;

  virtual void init() = 0;
  virtual void update(int) = 0;
  virtual void exit() = 0;
  
  virtual SystemType getType() const =0;
  
  virtual string toString() const;
};
