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
  Inputs(name, em), keyboard_(NULL), state_(NULL) {
}

CLInputs::~CLInputs() {
  delete state_;
  state_ = NULL;
}

void
CLInputs::init() {
  Resources *resources = _em.getComponent<Resources>();
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  keyboard_ = &(vc.getWindow().get_ic().get_keyboard());
  state_ = new CLInputState(keyboard_);
}

void
CLInputs::pumpEvents() {
  // Read messages from the windowing system message queue, if any are available:
  CL_KeepAlive::process();
}

InputState const *
CLInputs::getInputState() const {
  return state_;
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


