#pragma once
#include "Component.h"
#include "VisualContext.h"

// This class is called BVisual, because Visual is already used in XWindows
class BVisual: public Component {
private:
  bool gui_;
  
public:
  static const Type TYPE = VISUAL_TYPE;
  
  BVisual(bool gui=false);
  virtual ~BVisual();

  inline
  bool isGUI() const {
    return gui_;
  }
  inline
  void setGUI(bool gui) {
    gui_ = gui;
  }
  virtual void draw(VisualContext &vc, float x, float y, int delta=-1) = 0;
  virtual int getWidth(VisualContext &vc) const = 0;
  virtual int getHeight(VisualContext &vc) const = 0;

  virtual string toString() const;
};
