#pragma once
#include <string>

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
  const char *getTypeName() const;

  virtual string toString() const;
};
