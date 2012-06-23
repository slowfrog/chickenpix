#pragma once

#include <SFML/Graphics.hpp>

#include "../BVisual.h"

class SFMLVisualSprite: public BVisual {
private:
  sf::Sprite sprite;
  vector<Frame> frames;
  bool pingpong;
  int frame;
  int dir;
  int timeLeft;

public:
  SFMLVisualSprite(sf::Image &image, vector<Frame> const &frames, bool pingpong);
  virtual ~SFMLVisualSprite();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual string toString() const;
};
