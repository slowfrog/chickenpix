#pragma once

#include "SFML.h"
#include "../VisualText.h"

class SFMLVisualText: public VisualText {
private:
  sf::String	str_;
  sf::Font		&font_;
  sf::Color		color_;
  
public:
  SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color);
  virtual ~SFMLVisualText();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  
  virtual string toString() const;

  virtual void setText(const string &text);
  virtual CPColor getColor() const;
  virtual void setColor(const CPColor &color);
};
