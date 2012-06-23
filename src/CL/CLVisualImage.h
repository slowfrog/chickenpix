#pragma once
#include "CL.h"
#include "../BVisual.h"


class CLVisualImage: public BVisual {
private:
  CL_Image &image;
  
public:
  CLVisualImage(CL_Image &image);
  virtual ~CLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  
  virtual string toString() const;
};
