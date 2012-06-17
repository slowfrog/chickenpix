#include <sstream>
#include "Animated.h"

Animated::Animated(string const &name, vector<Frame> const &frames):
  Component(TYPE), name(name), frames(frames) {


}

Animated::~Animated() {
  frames.clear();
}

string
Animated::toString() const {
  ostringstream out;
  out << "{Animated name=" << name << ", frames=" << frames.size() << "}" << ends;
  return out.str();
}
