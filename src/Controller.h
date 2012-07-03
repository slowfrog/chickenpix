#pragma once

#include "Component.h"

class Controller: public Component {
private:
  string name_;
public:
  static const Type TYPE = CONTROLLER_TYPE;
  
  Controller(const string &name);
  virtual ~Controller();

  inline
  const string &getName() const {
    return name_;
  }
  
  inline
  void setName(const string &name) {
    name_ = name;
  }
  
  virtual string toString() const;
};
