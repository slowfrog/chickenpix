#pragma once
#include <SFML/Graphics.hpp>

#include "../Inputs.h"

class SFMLInputs: public Inputs {
private:
  sf::RenderWindow *window;
public:
  SFMLInputs(string const &name, EntityManager &em);
  virtual ~SFMLInputs();

  virtual bool isKeyDown(Key key) const;
  
  virtual void init();
  virtual void pumpEvents();
  virtual void exit();

  virtual string toString() const;
};
