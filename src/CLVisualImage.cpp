#include "CLVisualImage.h"

CLVisualImage::CLVisualImage(CL_Image &image):
  image(image) {
}

CLVisualImage::~CLVisualImage() {
}

void
CLVisualImage::render(CL_GraphicContext &gc, float x, float y) {
  image.draw(gc, x, y);
}

string
CLVisualImage::toString() const {
  return "{CLVisualImage}}";
}
