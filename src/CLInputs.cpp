#include <sstream>

#include <ClanLib/core.h>

#include "CLInputs.h"
#include "CLState.h"

CLInputs::CLInputs(string const &name, EntityManager &em):
  System(name, em), exitRequested(false), keyboard(NULL) {
}

CLInputs::~CLInputs() {
}

void
CLInputs::init() {
  CLState *clstate = em.getComponent<CLState>();
  keyboard = &(clstate->getWindow().get_ic().get_keyboard());
}

void
CLInputs::update(int now) {
  bool escape_down = keyboard->get_keycode(CL_KEY_ESCAPE);
  if (escape_down) {
    exitRequested = true;
  }
  // Read messages from the windowing system message queue, if any are available:
  CL_KeepAlive::process();
}

void
CLInputs::exit() {
}

bool
CLInputs::isExitRequested() const {
  return exitRequested;
}

string
CLInputs::toString() const {
  ostringstream out;
  out << "{CLInputs-System}" << ends;
  return out.str();
}


