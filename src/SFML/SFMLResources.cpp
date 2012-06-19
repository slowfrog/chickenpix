#include <sstream>
#include "SFMLResources.h"
#include "SFMLVisualImage.h"
#include "SFMLVisualSprite.h"
#include "SFMLVisualText.h"

SFMLResources::SFMLResources():
  Resources() {
}

SFMLResources::~SFMLResources() {
}

BVisual *
SFMLResources::makeImage(VisualContext &vc, string const &name) {
  SFMLResImage *resImage = (SFMLResImage *) getImage(name);
  return new SFMLVisualImage(resImage->get());
}

BVisual *
SFMLResources::makeSprite(VisualContext &vc, string const &name) {
  SFMLResSprite *resSprite = (SFMLResSprite *) getSprite(name);
  return new SFMLVisualSprite(resSprite->getImage(), resSprite->getFrames());
}

BVisual *
SFMLResources::makeText(VisualContext &vc, string const &text, string const &font) {
  SFMLResFont *resFont = (SFMLResFont *) getFont(font);
  return new SFMLVisualText(text, resFont->get(), sf::Color(255, 255, 255));
}

string
SFMLResources::toString() const {
  ostringstream out;
  out << "{SFMLResources " << "???" << "}" << ends;
  return out.str();
}
