#pragma once

#include "CLVisual.h"

class CLVisualImage: public CLVisual {
private:
  CL_Image &image;
  
public:
  CLVisualImage(CL_Image &image);
  virtual ~CLVisualImage();

  virtual void render(CL_GraphicContext &gc, float x, float y);
  
  virtual string toString() const;
};
