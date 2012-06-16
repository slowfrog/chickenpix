#include <sstream>
#include "Render.h"

Render::Render(string const &name, EntityManager &em):
  System(name, em) {
}

Render::~Render() {
}

void
Render::init() {
}

void
Render::exit() {
}

string
Render::toString() const {
  ostringstream out;
  out << "{Render-System name=" << getName() << "}" << ends;
  return out.str();
}
