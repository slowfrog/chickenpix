#include <sstream>

#include "SFMLVisualContext.h"
#include "SFMLVisualText.h"

SFMLVisualText::SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color):
  str_(text), font_(font), color_(color) {
  str_.SetSize(font_.GetCharacterSize());
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

string
SFMLVisualText::toString() const {
  ostringstream out;
  out << "{SFMLVisualText text=" << (string)str_.GetText() << "}" << ends;
  return out.str();
}
