#pragma once
#include "System.h"

class Render: public System {
public:
  Render(string const &name, EntityManager &em);
  virtual ~Render();
  virtual void init();
  virtual void exit();
  virtual string toString() const;
};
