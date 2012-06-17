#pragma once

#include <ClanLib/display.h>

#include "Component.h"

class CLVisual: public Component {
protected:
  CLVisual();
public:
  static const Type TYPE = CLVISUAL_TYPE;

  virtual ~CLVisual();

  virtual void render(CL_GraphicContext &gc,float x, float y) = 0;

  virtual string toString() const;
};

