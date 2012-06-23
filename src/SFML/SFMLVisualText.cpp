#include <sstream>

#include "SFMLVisualContext.h"
#include "SFMLVisualText.h"

SFMLVisualText::SFMLVisualText(string const &text, sf::Font &font, sf::Color const &color):
  str(text), font(font), color(color) {
  str.SetSize(font.GetCharacterSize());
  str.SetFont(font);
  str.SetColor(color);
}

SFMLVisualText::~SFMLVisualText() {
}

void
SFMLVisualText::draw(VisualContext &vc, float x, float y, int delta) {
  //sf::String line;
  //line.SetText(text);
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  str.SetPosition(x, y);
  rt.Draw(str);
}

string
SFMLVisualText::toString() const {
  ostringstream out;
  out << "{SFMLVisualText text=" << (string)str.GetText() << "}" << ends;
  return out.str();
}
