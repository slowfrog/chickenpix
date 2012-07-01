#pragma once
#include "CL.h"
#include "../VisualContext.h"

class CLVisualContext: public VisualContext {
private:
  CL_DisplayWindow &window_;

public:
  CLVisualContext(CL_DisplayWindow &window):
    window_(window) {
  }

  virtual ~CLVisualContext() {}

  inline
  CL_DisplayWindow &getWindow() {
    return window_;
  }
  
  inline
  CL_GraphicContext &getGraphicContext() {
    return window_.get_gc();
  }

  inline
  virtual int getWidth() const {
    return window_.get_geometry().get_width();
  }
  
  inline
  virtual int getHeight() const {
    return window_.get_geometry().get_height();
  }
};
