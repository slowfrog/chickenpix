#pragma once
#include <SFML/Graphics.hpp>
#include "../Render.h"

class SFMLRender: public Render {
public:
  sf::RenderWindow *window;
  
public:
  SFMLRender(string const &name, EntityManager &em);
  virtual ~SFMLRender();

  virtual void init();
  virtual VisualContext *getVisualContext();
  virtual void clear(VisualContext &vc);
  virtual void paint(VisualContext &vc);
  virtual void exit();

  virtual string toString() const;
};
