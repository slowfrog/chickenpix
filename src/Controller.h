#pragma once

#include "Component.h"

class Controller: public Component {
public:
  static const Type TYPE = CONTROLLER_TYPE;
  
  Controller();
  virtual ~Controller();

  virtual void update(int now) = 0;
  
  virtual string toString() const;
};
