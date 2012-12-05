/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
