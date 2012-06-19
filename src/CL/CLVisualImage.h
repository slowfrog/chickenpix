#pragma once

#include <ClanLib/display.h>
#include "BVisual.h"


class CLVisualImage: public BVisual {
private:
  CL_Image &image;
  
public:
  CLVisualImage(CL_Image &image);
  virtual ~CLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y);
  
  virtual string toString() const;
};
