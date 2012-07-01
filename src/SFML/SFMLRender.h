#pragma once
#include <SFML/Graphics.hpp>
#include "../Render.h"

class SFMLRender: public Render {
private:
  unsigned int width_;
  unsigned int height_;
  sf::RenderWindow *window_;
  
public:
  SFMLRender(string const &name, EntityManager &em, unsigned int width, unsigned int height);
  virtual ~SFMLRender();

  virtual void init();
  virtual VisualContext *getVisualContext();
  virtual void clear(VisualContext &vc);
  virtual void paint(VisualContext &vc);
  virtual void exit();

  virtual string toString() const;
};
