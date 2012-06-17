#pragma once
#include "System.h"

class SFMLLoader: public System {
private:
public:
  SFMLLoader(string const &name, EntityManager &em);
  virtual ~SFMLLoader();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};
