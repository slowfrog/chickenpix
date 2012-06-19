#pragma once

#include <SFML/Graphics.hpp>

#include "BVisual.h"

class SFMLVisualSprite: public BVisual {
private:
  sf::Sprite sprite;
  vector<Frame> frames;
  unsigned int frame;

public:
  SFMLVisualSprite(sf::Image &image, vector<Frame> const &frames);
  virtual ~SFMLVisualSprite();

  virtual void draw(VisualContext &vc, float x, float y);
  virtual string toString() const;
};
