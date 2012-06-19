#pragma once

#include "SFMLVisual.h"

class SFMLVisualText: public SFMLVisual {
private:
  sf::String	text;
  sf::Font		&font;
  sf::Color		color;
  
public:
  SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color);
  virtual ~SFMLVisualText();

  virtual void render(sf::RenderTarget &rt, float x, float y);
  
  virtual string toString() const;
};
