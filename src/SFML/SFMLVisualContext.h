#pragma once

#include <SFML/Graphics.hpp>

#include "../VisualContext.h"

class SFMLVisualContext: public VisualContext {
private:
  sf::RenderWindow &rw_;

public:
  SFMLVisualContext(sf::RenderWindow &rw):
    rw_(rw) {
  }

  virtual ~SFMLVisualContext() {}

  inline
  sf::RenderTarget &getRenderTarget() const {
    return rw_;
  }
  
  inline
  sf::RenderWindow &getRenderWindow() const {
    return rw_;
  }

  inline
  virtual int getWidth() const {
    return (int) rw_.GetWidth();
  }

  inline
  virtual int getHeight() const {
    return (int) rw_.GetHeight();
  }
};
