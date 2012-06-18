#pragma once
#include <SFML/Graphics.hpp>

#include "System.h"

class SFMLInputs: public System {
private:
  sf::RenderWindow *window;
  bool exitRequested;
public:
  SFMLInputs(string const &name, EntityManager &em);
  virtual ~SFMLInputs();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  bool isExitRequested() const;
  
  virtual string toString() const;

private:
  void moveHero(int now);
};
