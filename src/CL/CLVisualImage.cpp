#include "CLVisualContext.h"
#include "CLVisualImage.h"

CLVisualImage::CLVisualImage(CL_Image &image):
  image(image), rect() {
}

CLVisualImage::CLVisualImage(CL_Image &image, ImageRect rect):
  image(image), rect(rect) {
}

CLVisualImage::~CLVisualImage() {
}

void
CLVisualImage::draw(VisualContext &vc, float x, float y, int delta) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  if (rect.isValid()) {
    image.draw(gc, CL_Rectf(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h),
               CL_Rectf(x, y, x + rect.w, y + rect.h));
  } else {
    image.draw(gc, x, y);
  }
}

string
CLVisualImage::toString() const {
  return "{CLVisualImage}}";
}
