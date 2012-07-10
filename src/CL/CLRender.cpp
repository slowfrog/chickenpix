#include <sstream>
#include "../log.h"
#include "CLRender.h"
#include "CLResources.h"
#include "../Transform.h"
#include "../BVisual.h"
#include "CLVisualContext.h"

CLRender::CLRender(string const &name, unsigned int width, unsigned int height):
  Render(name), width_(width), height_(height), window_(NULL) {
}

CLRender::~CLRender() {
}

void
CLRender::init(EntityManager &em) {
  if (window_ == NULL) {
    window_ = new CL_DisplayWindow("CL chickenpix", width_, height_);
    // Must re-set the size on Linux, otherwise the window
    // frame eats some client area
    window_->set_size(width_, height_, true);
  }                                      
  Entity *clstate = em.createEntity();
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
CLRender::exit(EntityManager &em) {
  if (window_ != NULL) {
    delete window_;
    window_ = NULL;
  } else {
    LOG2 << "CLRender::exit has already been called\n";
  }
}

string
CLRender::toString() const {
  ostringstream out;
  out << "{CLRender-System name=" << getName() << " size=" << width_ << "x" << height_ << "}" <<ends;
  return out.str();
}
