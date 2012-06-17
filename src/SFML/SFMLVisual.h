#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class SFMLVisual: public Component {
protected:
  SFMLVisual();
public:
  static const Type TYPE = SFMLVISUAL_TYPE;

  virtual ~SFMLVisual();

  virtual void render(sf::RenderTarget &rt, float x, float y) = 0;

  virtual string toString() const;
};

