#pragma once
#include <vector>
#include "Component.h"
#include "Image.h"

class Animated: public Component {
private:
  string name;
  bool changed;
  
public:
  static const Type TYPE = ANIMATED_TYPE;

  Animated(string const &name);
  virtual ~Animated();

  string const &getAnimation() const;
  void setAnimation(string const &anim);
  bool hasChanged() const;
  void setChanged(bool changed);
  
  virtual string toString() const;
};
