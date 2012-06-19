#include "CLVisualContext.h"
#include "CLVisualImage.h"

CLVisualImage::CLVisualImage(CL_Image &image):
  BVisual(2), image(image) {
}

CLVisualImage::~CLVisualImage() {
}

void
CLVisualImage::draw(VisualContext &vc, float x, float y) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  image.draw(gc, x, y);
}

string
CLVisualImage::toString() const {
  return "{CLVisualImage}}";
}
