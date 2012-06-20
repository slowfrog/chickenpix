#pragma once

#include <SFML/Graphics.hpp>

#include "VisualContext.h"

class SFMLVisualContext: public VisualContext {
private:
  sf::RenderTarget &rt;

public:
  SFMLVisualContext(sf::RenderTarget &rt):
    rt(rt) {
  }

  virtual ~SFMLVisualContext() {}

  inline
  sf::RenderTarget &getRenderTarget() const {
    return rt;
  }
  
};
