#pragma once
#include "CL.h"
#include "../Render.h"

class CLRender: public Render {
private:
  unsigned int width_;
  unsigned int height_;
  CL_DisplayWindow *window_;
  
public:
  CLRender(string const &name, EntityManager &em, unsigned int width, unsigned int height);
  virtual ~CLRender();

  virtual void init();
  virtual VisualContext *getVisualContext();
  virtual void clear(VisualContext &vc);
  virtual void paint(VisualContext &vc);
  virtual void exit();

  virtual string toString() const;
};
