#include <sstream>
#include "System.h"

System::System(string const &name, EntityManager &em):
  _name(name), _em(em) {
}

System::~System() {
}

string const &
System::getName() const {
  return _name;
}

string
System::toString() const {
  ostringstream out;
  out << "{System name=" << _name << "}" << ends;
  return out.str();
}
