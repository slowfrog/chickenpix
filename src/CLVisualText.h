#pragma once

#include "CLVisual.h"

class CLVisualText: public CLVisual {
private:
  string text;
  CL_Font &font;
  CL_Colorf color;
  
public:
  CLVisualText(string const &text, CL_Font &font, CL_Colorf const &color);
  virtual ~CLVisualText();

  virtual void render(CL_GraphicContext &gc, float x, float y);
  
  virtual string toString() const;
};
