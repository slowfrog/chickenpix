#pragma once

#include "SFML.h"
#include "../BVisual.h"
#include "../Image.h"

class SFMLVisualImage: public BVisual {
private:
  sf::Sprite sprite_;
  ImageRect rect_;
public:
  SFMLVisualImage(sf::Image const &image);
  SFMLVisualImage(sf::Image const &image, ImageRect rect);
  virtual ~SFMLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual void debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  
  virtual string toString() const;
};
