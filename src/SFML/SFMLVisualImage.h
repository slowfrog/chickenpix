#pragma once

#include <SFML/Graphics.hpp>
#include "../BVisual.h"

class SFMLVisualImage: public BVisual {
private:
  sf::Sprite sprite;
public:
  SFMLVisualImage(sf::Image const &image);
  virtual ~SFMLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y);
  
  virtual string toString() const;
};
