#pragma once

#include <SFML/Graphics.hpp>

#include "BVisual.h"

class SFMLVisualText: public BVisual {
private:
  sf::String	str;
  sf::Font		&font;
  sf::Color		color;
  
public:
  SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color);
  virtual ~SFMLVisualText();

  virtual void draw(VisualContext &vc, float x, float y);
  
  virtual string toString() const;
};
