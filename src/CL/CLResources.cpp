#include <sstream>
#include "CLResources.h"

CLResources::CLResources():
  Resources() {
}

CLResources::~CLResources() {
}

string
CLResources::toString() const {
  ostringstream out;
  out << "{CLResources " << "???" << "}" << ends;
  return out.str();
}
