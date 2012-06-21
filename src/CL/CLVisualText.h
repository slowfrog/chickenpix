#pragma once
#include "CL.h"
#include "../BVisual.h"

class CLVisualText: public BVisual {
private:
  string text;
  CL_Font &font;
  CL_Colorf color;
  
public:
  CLVisualText(string const &text, CL_Font &font, CL_Colorf const &color);
  virtual ~CLVisualText();

  virtual void draw(VisualContext &vc, float x, float y);
  
  virtual string toString() const;
};
