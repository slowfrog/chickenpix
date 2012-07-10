#include <sstream>
#include "System.h"

// Constructor
System::System(const std::string& name):
_name( name){}

System::~System() {
}

// 
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
