#pragma once

#include "Component.h"

class Actionable: public Component {
private:
  string action_;
  
public:
  static Type TYPE;
  
  Actionable();
  virtual ~Actionable();

  void setAction(const string &action);
  const string &getAction() const;
  void clearAction();
  
  virtual string toString() const;
};
