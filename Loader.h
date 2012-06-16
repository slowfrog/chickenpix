#pragma once
#include "System.h"
#include "Image.h"

class Loader: public System {
public:
  Loader(string const &name, EntityManager &em);
  virtual ~Loader();
  virtual void init();
  virtual void exit();
  virtual string toString() const;
};
