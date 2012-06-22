#include <sstream>

#include "CLInputs.h"
#include "CLVisualContext.h"
#include "../Input.h"
#include "../Resources.h"
#include "../Transform.h"

int KEYMAP[] = {
  CL_KEY_0,
  CL_KEY_1,
  CL_KEY_2,
  CL_KEY_3,
  CL_KEY_4,
  CL_KEY_5,
  CL_KEY_6,
  CL_KEY_7,
  CL_KEY_8,
  CL_KEY_9,
  CL_KEY_SPACE,
  CL_KEY_UP,
  CL_KEY_DOWN,
  CL_KEY_LEFT,
  CL_KEY_RIGHT,
  CL_KEY_ESCAPE
};


CLInputs::CLInputs(string const &name, EntityManager &em):
  Inputs(name, em), keyboard(NULL) {
}

CLInputs::~CLInputs() {
}

void
CLInputs::init() {
  Resources *resources = em.getComponent<Resources>();
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  keyboard = &(vc.getWindow().get_ic().get_keyboard());
}

void
CLInputs::pumpEvents() {
  // Read messages from the windowing system message queue, if any are available:
  CL_KeepAlive::process();
}

bool
CLInputs::isKeyDown(Key key) const {
  return keyboard->get_keycode(KEYMAP[key]);
}

void
CLInputs::exit() {
}

string
CLInputs::toString() const {
  ostringstream out;
  out << "{CLInputs-System}" << ends;
  return out.str();
}


