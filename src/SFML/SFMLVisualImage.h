#pragma once

#include <SFML/Graphics.hpp>
#include "../BVisual.h"
#include "../Image.h"

class SFMLVisualImage: public BVisual {
private:
  sf::Sprite sprite;
  ImageRect rect;
public:
  SFMLVisualImage(sf::Image const &image);
  SFMLVisualImage(sf::Image const &image, ImageRect rect);
  virtual ~SFMLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  
  virtual string toString() const;
};
