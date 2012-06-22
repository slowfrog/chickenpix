#include <sstream>
#include "Animated.h"

Animated::Animated(string const &name):
  Component(TYPE), name(name), changed(true) {
}

Animated::~Animated() {
}

string const &
Animated::getAnimation() const {
  return name;
}

void
Animated::setAnimation(string const &anim) {
  if (name != anim) {
    name = anim;
    changed = true;
  }
}

bool
Animated::hasChanged() const {
  return changed;
}

void
Animated::setChanged(bool newChanged) {
  changed = newChanged;
}

string
Animated::toString() const {
  ostringstream out;
  out << "{Animated name=" << name << "}" << ends;
  return out.str();
}
