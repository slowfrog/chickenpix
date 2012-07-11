#pragma once
#include "CL.h"
#include "../BVisual.h"
#include "../Image.h"


class CLVisualImage: public BVisual {
private:
  CL_Image &image_;
  ImageRect rect_;
  
public:
  CLVisualImage(CL_Image &image);
  CLVisualImage(CL_Image &image, ImageRect rect);
  virtual ~CLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual void debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  virtual string toString() const;
};
