#pragma once
#include "CL.h"
#include "../BVisual.h"

class CLVisualText: public BVisual {
private:
  string text_;
  CL_Font &font_;
  CL_Colorf color_;
  mutable int width_;
  mutable int height_;
  
public:
  CLVisualText(string const &text, CL_Font &font, CL_Colorf const &color);
  virtual ~CLVisualText();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  
  virtual string toString() const;

private:
  void computeSize(VisualContext &vc) const;
};
