#include <sstream>

#include "CLInputs.h"
#include "CLVisualContext.h"
#include "../Input.h"
#include "../Resources.h"
#include "../Transform.h"

CLInputs::CLInputs(string const &name):
  Inputs(name), keyboard_(NULL), mouse_(NULL), state_(NULL) {
}

CLInputs::~CLInputs() {
  delete state_;
  state_ = NULL;
}

void
CLInputs::init(EntityManager &em) {
  Inputs::init(em);
  Resources *resources = em.getComponent<Resources>();
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  keyboard_ = &(vc.getWindow().get_ic().get_keyboard());
  mouse_ = &(vc.getWindow().get_ic().get_mouse());
  state_ = new CLInputState(vc, keyboard_, mouse_);
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
CLInputs::exit(EntityManager &em) {
}

string
CLInputs::toString() const {
  ostringstream out;
  out << "{CLInputs-System " << getName() << "}" << ends;
  return out.str();
}


