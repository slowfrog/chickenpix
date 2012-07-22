#pragma once
#include "Component.h"
#include "VisualContext.h"

// This class is called BVisual, because Visual is already used in XWindows
class BVisual: public Component {
private:
  float cx_;
  float cy_;
  int zOrder_;
  bool gui_;
  
public:
  static Type TYPE;
  
  BVisual(float cx, float cy, int zOrder=0, bool gui=false);
  BVisual(int zOrder=0, bool gui=false);
  virtual ~BVisual();

  inline
  float getCenterX() const {
    return cx_;
  }
  inline
  void setCenterX(float cx) {
    cx_ = cx;
  }
  inline
  float getCenterY() const {
    return cy_;
  }
  inline
  void setCenterY(float cy) {
    cy_ = cy;
  }
  inline
  void setCenter(float cx, float cy) {
    cx_ = cx;
    cy_ = cy;
  }
  
  inline
  int getZOrder() const {
    return zOrder_;
  }
  inline
  void setZOrder(int zOrder) {
    zOrder_ = zOrder;
  }

  static bool compareZOrder(BVisual const &visual1, BVisual const &visual2);
  
  inline
  bool isGUI() const {
    return gui_;
  }
  inline
  void setGUI(bool gui) {
    gui_ = gui;
  }
  virtual void draw(VisualContext &vc, float x, float y, int delta=-1) = 0;
  virtual void debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom) {
    draw(vc, x, y, delta);
  }
  virtual int getWidth(VisualContext &vc) const = 0;
  virtual int getHeight(VisualContext &vc) const = 0;

  virtual inline
  bool isText() const {
    return false;
  }

  virtual string toString() const;
};
