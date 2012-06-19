#pragma once
#include <map>

#include "Component.h"

class Resources : public Component {
public:
  enum Kind {
    Image = 0,
    Sprite = 1,
    Font = 2
  };
  static const unsigned int KINDS = 3;
  
private:
  map<string, void*> store[KINDS];

public:
  static const Type TYPE = RESOURCES_TYPE;

  Resources();
  virtual ~Resources();

  void setObject(Kind kind, string const &name, void *object);
  
  void *getObject(Kind kind, string const &name);
  
  virtual string toString() const;
};

