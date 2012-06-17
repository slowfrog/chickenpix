#include <sstream>
#include "CLState.h"

CLState::CLState(CL_DisplayWindow &window):
  Component(TYPE), window(window) {
}

CLState::~CLState() {
}

CL_DisplayWindow &
CLState::getWindow() {
  return window;
}

CL_GraphicContext &
CLState::getGC() {
  return window.get_gc();
}

string
CLState::toString() const {
  ostringstream out;
  out << "{CLState}" << ends;
  return out.str();
}
