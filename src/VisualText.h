#pragma once

#include "BVisual.h"
#include "Resources.h"

class VisualText: public BVisual {
protected:
  string text_;
public:
  VisualText(const string &text);
  virtual ~VisualText();

  virtual const string &getText() const;
  virtual void setText(const string &text);
  virtual CPColor getColor() const=0;
  virtual void setColor(const CPColor &color)=0;
};
