#pragma once

#include <SFML/Graphics.hpp>

#include "../VisualContext.h"

class SFMLVisualContext: public VisualContext {
private:
  sf::RenderWindow &rw;

public:
  SFMLVisualContext(sf::RenderWindow &rw):
    rw(rw) {
  }

  virtual ~SFMLVisualContext() {}

  inline
  sf::RenderTarget &getRenderTarget() const {
    return rw;
  }
  
  inline
  sf::RenderWindow &getRenderWindow() const {
    return rw;
  }
  
};
