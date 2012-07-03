#pragma once
#include "System.h"
#include "VisualContext.h"

class Render: public System {
private:
  int last;
public:
  Render(string const &name, EntityManager &em);
  virtual ~Render();

  virtual void init() = 0;
  virtual VisualContext *getVisualContext() = 0;
  virtual void clear(VisualContext &vc) = 0;
  virtual void update(int now);
  virtual void paint(VisualContext &vc) = 0;
  virtual void exit() = 0;
  
  inline SystemType getType() const { return RENDER_TYPE;}

  virtual string toString() const;
};
