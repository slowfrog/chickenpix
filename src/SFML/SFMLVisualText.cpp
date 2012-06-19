#include <sstream>

#include "SFMLVisualText.h"

SFMLVisualText::SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color):
  text(text), font(font), color(color) {
}

SFMLVisualText::~SFMLVisualText() {
}

void
SFMLVisualText::render(sf::RenderTarget &rt, float x, float y) {
  //sf::String line;
  //line.SetText(text);
  text.SetSize(30);
  text.SetFont(font);
  text.SetColor(color);
  text.SetPosition(x, y);
  rt.Draw(text);
}

string
SFMLVisualText::toString() const {
  ostringstream out;
  out << "{SFMLVisualText text=" << (string)text.GetText() << "}" << ends;
  return out.str();
}
