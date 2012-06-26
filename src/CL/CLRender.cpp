#include <sstream>
#include "CLRender.h"
#include "CLResources.h"
#include "../Transform.h"
#include "../BVisual.h"
#include "CLVisualContext.h"

CLRender::CLRender(string const &name, EntityManager &em):
  Render(name, em), window(NULL) {
}

CLRender::~CLRender() {
}

void
CLRender::init() {
  window = new CL_DisplayWindow("CL chickenpix", 640, 480);
  window->set_size(640, 480, true); // Must re-set the size on Linux, otherwise the window
                                    // frame eats some client area
  Entity *clstate = em.createEntity();
  clstate->addComponent(new CLResources(*window));
}

VisualContext *
CLRender::getVisualContext() {
  return new CLVisualContext(*window);
}

void
CLRender::clear(VisualContext &vc) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  gc.clear(CL_Colorf::black);
}

void
CLRender::paint(VisualContext &vc) {
  ((CLVisualContext &)vc).getWindow().flip();
}

void
CLRender::exit() {
  delete window;
  window = NULL;
}

string
CLRender::toString() const {
  ostringstream out;
  out << "{CLRender-System name=" << getName() << "}" << ends;
  return out.str();
}
