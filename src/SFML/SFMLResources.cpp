#include <cassert>
#include <iostream>
#include <sstream>
#include "SFMLResources.h"
#include "SFMLAudio.h"
#include "SFMLVisualImage.h"
#include "SFMLVisualSprite.h"
#include "SFMLVisualText.h"

SFMLResources::SFMLResources(sf::RenderWindow &rw):
  Resources(), vc_(rw) {
}

SFMLResources::~SFMLResources() {
}

VisualContext &
SFMLResources::getVisualContext() {
  return vc_;
}

BVisual *
SFMLResources::makeImage(string const &name) {
  SFMLResImage *resImage = (SFMLResImage *) getImage(name);
  if (resImage == NULL) {
    cerr << "Cannot find image: " << name << endl;
    assert(!(resImage == NULL));
  }
  return new SFMLVisualImage(resImage->get());
}

BVisual *
SFMLResources::makeImage(ImagePart const part) {
  SFMLResImage *resImage = (SFMLResImage *) getImage(part.name);
  if (resImage == NULL) {
    cerr << "Cannot find image: " << part.name << endl;
    assert(!(resImage == NULL));
  }
  return new SFMLVisualImage(resImage->get(), part.rect);
}

BVisual *
SFMLResources::makeSprite(string const &name) {
  SFMLResSprite *resSprite = (SFMLResSprite *) getSprite(name);
  if (resSprite == NULL) {
    cerr << "Cannot find sprite: " << name << endl;
    assert(!(resSprite == NULL));
  }
 SFMLVisualSprite *sprite = new SFMLVisualSprite(resSprite->getImage(),
                                                 resSprite->getFrames(),
                                                 resSprite->isPingPong());
 sprite->setCenter((float) sprite->getWidth(vc_) / 2, 
                   (float) sprite->getHeight(vc_) / 2);
 return sprite;
}

BVisual *
SFMLResources::makeText(string const &text, string const &font, CPColor const &color) {
  SFMLResFont *resFont = (SFMLResFont *) getFont(font);
  if (resFont == NULL) {
    cerr << "Cannot find font: " << font << endl;
    assert(!(resFont == NULL));
  }
  return new SFMLVisualText(text, resFont->get(), sf::Color(color.r, color.g, color.b, color.a));
}

Audio *
SFMLResources::makeAudio(string const &name, bool looping) {
  SFMLResAudio *resAudio = (SFMLResAudio *) getAudio(name);
  if (resAudio == NULL) {
    cerr << "Cannot find audio: " << name << endl;
    assert(!(resAudio == NULL));
  }
  return new SFMLAudio(name, looping, resAudio->get());
}


string
SFMLResources::toString() const {
  ostringstream out;
  out << "{SFMLResources " << "???" << "}" << ends;
  return out.str();
}
