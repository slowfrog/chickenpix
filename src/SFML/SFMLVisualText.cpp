/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
  str_.SetColor(color_);
}


string
SFMLVisualText::toString() const {
  ostringstream out;
  out << "{SFMLVisualText text=" << (string)str_.GetText() << "}" << ends;
  return out.str();
}
