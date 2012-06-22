#pragma once

#include <string>

#include "Component.h"

class Scriptable: public Component {
private:
  string name;
public:
  static const Type TYPE = SCRIPTABLE_TYPE;
  Scriptable(string const &name);
  virtual ~Scriptable();

  inline string const &getName() const {
    return name;
  }
  virtual void update(int now);

  virtual string toString() const;
};
