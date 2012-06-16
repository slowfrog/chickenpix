#pragma once
#include "Component.h"

class Input: public Component {
public:
  static const Type TYPE = INPUT_TYPE;

  Input();
  virtual ~Input();
  virtual string toString() const;
};
