#pragma once
#include <string>
#include "Notification.h"
#include "SystemRegistry.h"
#include "EntityManager.h"

using namespace std;

/*
 System interface
*/
class System {
protected:
  string _name;
  
public:
  System(const std::string&);
  virtual ~System();
  
  string const &getName() const;

  virtual void init   ( EntityManager &)      = 0;
  virtual void update ( EntityManager &, int) = 0;
  virtual void exit   ( EntityManager &)      = 0;
  
  virtual SystemType getType() const =0;
  
  virtual string toString() const;
};
