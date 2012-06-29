#pragma once
#include "Component.h"
#include "VisualContext.h"

// This class is called BVisual, because Visual is already used in XWindows
class BVisual: public Component {
  
public:
  static const Type TYPE = VISUAL_TYPE;
  
  BVisual();
  virtual ~BVisual();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1) = 0;

  virtual string toString() const;
};
