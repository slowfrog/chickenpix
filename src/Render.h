#pragma once
#include "System.h"
#include "VisualContext.h"

class Render: public System {
private:
  int last;
public:
  Render( string const &name);
  virtual ~Render();

  // System interface
  virtual void init   ( EntityManager&) = 0;
  virtual void update ( EntityManager&, int now);
  virtual void exit   ( EntityManager&) = 0;
  
  // Render interface
  virtual VisualContext *getVisualContext() = 0;
  virtual void clear( VisualContext &vc) = 0;
  virtual void paint( VisualContext &vc) = 0;
  
  
  inline SystemType getType() const { return RENDER_TYPE;}

  virtual string toString() const;

private:
  void applyCameraConstraints(EntityManager &em, Entity *cameraEntity);
};
