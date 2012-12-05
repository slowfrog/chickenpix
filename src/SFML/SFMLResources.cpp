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
  SFMLVisualImage *image = new SFMLVisualImage(resImage->get());
  image->setCenter((float) image->getWidth(vc_) / 2, 
                   (float) image->getHeight(vc_) / 2);
  return image;
}

BVisual *
SFMLResources::makeImage(ImagePart const part) {
  SFMLResImage *resImage = (SFMLResImage *) getImage(part.name);
  if (resImage == NULL) {
    cerr << "Cannot find image: " << part.name << endl;
    assert(!(resImage == NULL));
  }
  SFMLVisualImage *image = new SFMLVisualImage(resImage->get(), part.rect);
  image->setCenter((float) image->getWidth(vc_) / 2, 
                   (float) image->getHeight(vc_) / 2);
  return image;
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
  SFMLVisualText *vtext =
    new SFMLVisualText(text, resFont->get(),
                       sf::Color(color.r, color.g, color.b, color.a));
  return vtext;
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
