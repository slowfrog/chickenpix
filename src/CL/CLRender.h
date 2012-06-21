#pragma once
#include "CL.h"
#include "../Render.h"

class CLRender: public Render {
public:
  CL_DisplayWindow *window;
  
public:
  CLRender(string const &name, EntityManager &em);
  virtual ~CLRender();

  virtual void init();
  virtual VisualContext *getVisualContext();
  virtual void clear(VisualContext &vc);
  virtual void paint(VisualContext &vc);
  virtual void exit();

  virtual string toString() const;
};
