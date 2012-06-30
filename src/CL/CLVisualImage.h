#pragma once
#include "CL.h"
#include "../BVisual.h"
#include "../Image.h"


class CLVisualImage: public BVisual {
private:
  CL_Image &image;
  ImageRect rect;
  
public:
  CLVisualImage(CL_Image &image);
  CLVisualImage(CL_Image &image, ImageRect rect);
  virtual ~CLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  
  virtual string toString() const;
};
