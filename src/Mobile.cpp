#include <sstream>
#include "Mobile.h"

Mobile::Mobile(float dx, float dy):
  Component(TYPE), dx(dx), dy(dy) {
}

Mobile::~Mobile() {
}

string
Mobile::toString() const {
  ostringstream out;
  out << "{Mobile dx=" << dx << ", dy=" << dy << "}" << ends;
  return out.str();
};
