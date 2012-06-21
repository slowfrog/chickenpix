#pragma once
#include "CL.h"
#include "../Component.h"

class CLState: public Component {
private:
  CL_DisplayWindow &window;

public:
  static const Type TYPE = CLSTATE_TYPE;

  CLState(CL_DisplayWindow &window);
  virtual ~CLState();

  CL_DisplayWindow &getWindow();
  CL_GraphicContext &getGC();

  virtual string toString() const;
};
