#pragma once

#include "Component.h"
#include <vector>

class Controller: public Component {
private:
  vector<string> names_;
  
public:
  static Type TYPE;
  
  Controller(const string &name);
  virtual ~Controller();

  inline
  const vector<string> &getNames() const {
    return names_;
  }
  
  void addName(const string &name);
  void removeName(const string &name);
  
  virtual string toString() const;
};
