#pragma once
#include "System.h"
#include "Image.h"

class Loader: public System {
public:
  Loader(string const &name, EntityManager &em);
  virtual ~Loader();
  virtual void init();
  virtual void update(int now);
  virtual void exit();
  virtual void loadLevel(string const &name);
  virtual string toString() const;
};
