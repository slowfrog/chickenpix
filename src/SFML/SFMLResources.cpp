#include <sstream>
#include "SFMLResources.h"
#include "SFMLVisualImage.h"
#include "SFMLVisualSprite.h"
#include "SFMLVisualText.h"

SFMLResources::SFMLResources(sf::RenderWindow &rw):
  Resources(), vc(rw) {
}

SFMLResources::~SFMLResources() {
}

VisualContext &
SFMLResources::getVisualContext() {
  return vc;
}

BVisual *
SFMLResources::makeImage(string const &name) {
  SFMLResImage *resImage = (SFMLResImage *) getImage(name);
  return new SFMLVisualImage(resImage->get());
}

BVisual *
SFMLResources::makeSprite(string const &name) {
  SFMLResSprite *resSprite = (SFMLResSprite *) getSprite(name);
  return new SFMLVisualSprite(resSprite->getImage(), resSprite->getFrames());
}

BVisual *
SFMLResources::makeText(string const &text, string const &font) {
  SFMLResFont *resFont = (SFMLResFont *) getFont(font);
  return new SFMLVisualText(text, resFont->get(), sf::Color(255, 255, 255));
}

string
SFMLResources::toString() const {
  ostringstream out;
  out << "{SFMLResources " << "???" << "}" << ends;
  return out.str();
}
