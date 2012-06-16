#include <sstream>
#include "CLRender.h"
#include "CLState.h"

CLRender::CLRender(string const &name, EntityManager &em):
  System(name, em), window(NULL) {
}

CLRender::~CLRender() {
  delete window;
  window = NULL;
}

void
CLRender::init() {
  window = new CL_DisplayWindow("Hello World", 640, 480);
  Entity *clstate = em.createEntity();
  clstate->addComponent(new CLState(*window));
}

void
CLRender::update(int now) {
}

void
CLRender::exit() {
}

string
CLRender::toString() const {
  ostringstream out;
  out << "{CLRender-System name=" << getName() << "}" << ends;
  return out.str();
}
