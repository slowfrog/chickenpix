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
    image_.draw(gc, CL_Rectf(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h),
               CL_Rectf(x, y, x + rect_.w, y + rect_.h));
  } else {
    image_.draw(gc, x, y);
  }
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
