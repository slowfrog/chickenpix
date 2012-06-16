#pragma once
#include "System.h"

class CLLoader: public System {
private:
public:
  CLLoader(string const &name, EntityManager &em);
  virtual ~CLLoader();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};
