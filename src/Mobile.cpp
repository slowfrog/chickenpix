#include <sstream>
#include "Mobile.h"

Mobile::Mobile():
  Component(TYPE), dx_(0.0f), dy_(0.0f) {
}

Mobile::Mobile(float dx, float dy):
  Component(TYPE), dx_(dx), dy_(dy) {
}

Mobile::~Mobile() {
}

string
Mobile::toString() const {
  ostringstream out;
  out << "{Mobile dx=" << dx_ << ", dy=" << dy_ << "}" << ends;
  return out.str();
};
