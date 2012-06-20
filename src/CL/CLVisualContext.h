#pragma once

#include <ClanLib/display.h>

#include "VisualContext.h"

class CLVisualContext: public VisualContext {
private:
  CL_DisplayWindow &window;

public:
  CLVisualContext(CL_DisplayWindow &window):
    window(window) {
  }

  virtual ~CLVisualContext() {}

  inline
  CL_DisplayWindow &getWindow() {
    return window;
  }
  
  inline
  CL_GraphicContext &getGraphicContext() {
    return window.get_gc();
  }
  
};
