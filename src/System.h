#pragma once
#include <string>
#include "EntityManager.h"

using namespace std;

// List of system available
// Add here new system
typedef enum {
  LOADER_TYPE     =0,
  RENDER_TYPE,
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  ANIMATION_TYPE,
  // - Do not add anything after this line!! (just before)
  END_OF_LIST,
  MAX_SYSTEM = END_OF_LIST
} SystemType;

// Useful way to call system methods in wanted order
// to discuss !!!!!
static SystemType in_ex_itPath[]={
  RENDER_TYPE,
  ANIMATION_TYPE,
  LOADER_TYPE,
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  END_OF_LIST
};

static SystemType updatePath[]={
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  ANIMATION_TYPE,
  RENDER_TYPE,
  END_OF_LIST
};

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
