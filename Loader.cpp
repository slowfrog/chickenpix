#include <sstream>
#include "Loader.h"

Loader::Loader(string const &name, EntityManager &em):
  System(name, em) {
}

Loader::~Loader() {
}

void
Loader::init() {
}

void
Loader::exit() {
}

string
Loader::toString() const {
  ostringstream out;
  out << "{Loader-system name=" << getName() << "}" << ends;
  return out.str();
}
