#include <sstream>
#include "CLRender.h"
#include "CLResources.h"
#include "../Transform.h"
#include "../BVisual.h"
#include "CLVisualContext.h"

CLRender::CLRender(string const &name, EntityManager &em, unsigned int width, unsigned int height):
  Render(name, em), width_(width), height_(height), window_(NULL) {
}

CLRender::~CLRender() {
}

void
CLRender::init() {
  window_ = new CL_DisplayWindow("CL chickenpix", width_, height_);
  window_->set_size(width_, height_, true); // Must re-set the size on Linux, otherwise the window
                                            // frame eats some client area
  Entity *clstate = _em.createEntity();
  clstate->addComponent(new CLResources(*window_));
}

VisualContext *
CLRender::getVisualContext() {
  return new CLVisualContext(*window_);
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
  delete window_;
  window_ = NULL;
}

string
CLRender::toString() const {
  ostringstream out;
  out << "{CLRender-System name=" << getName() << " size=" << width_ << "x" << height_ << "}" <<ends;
  return out.str();
}
