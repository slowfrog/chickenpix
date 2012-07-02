#pragma once

#include "Controller.h"

class HeroController: public Controller {
public:
  HeroController();
  virtual ~HeroController();

  virtual void update(int now);
  
  virtual string toString() const;
};
