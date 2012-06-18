#include <sstream>

#include "SFMLVisualText.h"

SFMLVisualText::SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color):
  text(text), font(font), color(color) {
}

SFMLVisualText::~SFMLVisualText() {
}

void
SFMLVisualText::render(sf::RenderTarget &rt, float x, float y) {
  sf::String line;
  line.SetText(text);
  line.SetFont(font);
  line.SetColor(color);
  line.SetPosition(x, y);
  rt.Draw(line);
}

string
SFMLVisualText::toString() const {
  ostringstream out;
  out << "{SFMLVisualText text=" << text << "}" << ends;
  return out.str();
}
