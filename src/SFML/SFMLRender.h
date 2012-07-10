#pragma once
#include "SFML.h"
#include "../Render.h"

class SFMLRender: public Render {
private:
  unsigned int width_;
  unsigned int height_;
  sf::RenderWindow *window_;
  static bool mWindowReady;
  
public:
  SFMLRender(string const &name, unsigned int width, unsigned int height);
  virtual ~SFMLRender();

  virtual void init( EntityManager &);
  virtual VisualContext *getVisualContext();
  virtual void clear(VisualContext &vc);
  virtual void paint(VisualContext &vc);
  virtual void exit( EntityManager &);

  virtual string toString() const;
};
