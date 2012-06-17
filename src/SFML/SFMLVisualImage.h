#pragma once
#include "SFMLVisual.h"

class SFMLVisualImage: public SFMLVisual {
private:
  sf::Sprite sprite;
public:
  SFMLVisualImage(sf::Sprite const &sprite);
  virtual ~SFMLVisualImage();

  virtual void render(sf::RenderTarget &rt, float x, float y);
  
  virtual string toString() const;
};
