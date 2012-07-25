#pragma once

#include "Component.h"

class GUI: public Component {

public:
  static Type TYPE;
  
  GUI();
  virtual ~GUI();

  virtual string toString() const;
};
