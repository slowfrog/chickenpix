#pragma once
#include <string>
#include "ComponentRegistry.h"

using namespace std;

class Entity;

class Component {
public:
  typedef unsigned short Type;
  
private:
  Type type_;

public:
  explicit Component(Type type);
  virtual ~Component();

  inline Type getType() const {
    return type_;
  }
  inline const char *getTypeName() const {
    return ComponentName[type_];
  }

  virtual string toString() const;
};
