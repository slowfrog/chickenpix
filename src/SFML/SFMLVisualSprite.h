#pragma once

#include "SFML.h"
#include "../BVisual.h"
#include "../Image.h"

class SFMLVisualSprite: public BVisual {
private:
  sf::Sprite sprite_;
  vector<Frame> frames_;
  bool pingpong_;
  int frame_;
  int dir_;
  int timeLeft_;

public:
  SFMLVisualSprite(sf::Image &image, vector<Frame> const &frames, bool pingpong);
  virtual ~SFMLVisualSprite();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  
  virtual string toString() const;
};
