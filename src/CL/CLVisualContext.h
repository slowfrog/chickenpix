#pragma once

#include <ClanLib/display.h>

#include "VisualContext.h"

class CLVisualContext: public VisualContext {
private:
  CL_GraphicContext &gc;

public:
  CLVisualContext(CL_GraphicContext &gc):
    gc(gc) {
  }

  virtual ~CLVisualContext() {}

  inline
  CL_GraphicContext &getGraphicContext() {
    return gc;
  }
  
};
