#include <sstream>
#include "System.h"

System::System(string const &name):
  name(name) {
}

System::~System() {
}

string const &
System::getName() const {
  return name;
}

string
System::toString() const {
  ostringstream out;
  out << "{System name=" << name << "}" << ends;
  return out.str();
}
