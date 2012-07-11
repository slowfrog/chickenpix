#include <sstream>

#include "SFMLVisualContext.h"
#include "SFMLVisualText.h"

SFMLVisualText::SFMLVisualText(string const &text, sf::Font &font,
                               sf::Color const &color):
  VisualText(text),
  str_(text), font_(font), color_(color) {
  str_.SetSize((float) font_.GetCharacterSize());
  str_.SetFont(font_);
  str_.SetColor(color_);
}

SFMLVisualText::~SFMLVisualText() {
}

void
SFMLVisualText::draw(VisualContext &vc, float x, float y, int delta) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  str_.SetPosition(x, y);
  rt.Draw(str_);
}

int
SFMLVisualText::getWidth(VisualContext &) const {
  return (int) str_.GetRect().GetWidth();
}

int
SFMLVisualText::getHeight(VisualContext &) const {
  return (int) str_.GetRect().GetHeight();
}

void
SFMLVisualText::setText(const string &text) {
  VisualText::setText(text);
  str_.SetText(text);
}

CPColor
SFMLVisualText::getColor() const {
  return CPColor(color_.r, color_.g, color_.b, color_.a);
}

void
SFMLVisualText::setColor(const CPColor &color) {
  color_ = sf::Color(color.r, color.g, color.b, color.a);
}


string
SFMLVisualText::toString() const {
  ostringstream out;
  out << "{SFMLVisualText text=" << (string)str_.GetText() << "}" << ends;
  return out.str();
}
