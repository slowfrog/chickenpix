#pragma once
#include <string>
#include "ComponentRegistry.h"

using namespace std;

class Component {
public:
  typedef unsigned short Type;
  
private:
  Type type;

public:
  explicit Component(Type type);
  virtual ~Component();

  inline Type getType() const {
    return type;
  }
  inline const char *getTypeName() const {
    return ComponentName[type];
  }

  virtual string toString() const;
};
