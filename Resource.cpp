#include <sstream>
#include "Resource.h"

Resource::Resource():
  Component(TYPE) {
}

Resource::~Resource() {
  framesMap.clear();
}

void
Resource::addFrames(string const &name, vector<Frame> const &frames) {
  framesMap[name] = frames;
}

string
Resource::toString() const {
  ostringstream out;
  out << "{Resource frames=" << framesMap.size() << "}" << ends;
  return out.str();
}
