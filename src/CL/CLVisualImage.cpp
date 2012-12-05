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
 
#include "CLVisualContext.h"
#include "CLVisualImage.h"

CLVisualImage::CLVisualImage(CL_Image &image):
  image_(image), rect_() {
}

CLVisualImage::CLVisualImage(CL_Image &image, ImageRect rect):
  image_(image), rect_(rect) {
}

CLVisualImage::~CLVisualImage() {
}

void
CLVisualImage::draw(VisualContext &vc, float x, float y, int delta) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  if (rect_.isValid()) {
    image_.draw(gc, CL_Rectf((float) rect_.x, (float) rect_.y, 
                             (float) rect_.x + rect_.w, (float) rect_.y + rect_.h),
               CL_Rectf(x, y, x + rect_.w, y + rect_.h));
  } else {
    image_.draw(gc, x, y);
  }
}

void
CLVisualImage::debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom) {
  // Draw base visual
  draw(vc, x, y, delta);

  // For debugging: show a red outline
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  float cx = x + getWidth(vc) / 2;
  float cy = y + getHeight(vc) / 2;
  CL_Draw::box(gc, cx - left, cy - top, cx + right, cy + bottom,
               CL_Colorf(1.0f, 0.0f, 0.0f, 0.3f));
}

int
CLVisualImage::getWidth(VisualContext &) const {
  return rect_.isValid() ? rect_.w : image_.get_width();
}

int
CLVisualImage::getHeight(VisualContext &) const {
  return rect_.isValid() ? rect_.h : image_.get_height();
}


string
CLVisualImage::toString() const {
  return "{CLVisualImage}}";
}
