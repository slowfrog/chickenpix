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
#include <sstream>
#include "CLResources.h"
#include "CLAudio.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"

CLResources::CLResources(CL_DisplayWindow &window):
  Resources(), vc_(window) {
}

CLResources::~CLResources() {
}

VisualContext &
CLResources::getVisualContext() {
  return vc_;
}

BVisual *
CLResources::makeImage(string const &name) {
  CLResImage *resImage = (CLResImage *) getImage(name);
  if (resImage == NULL) {
    cerr << "Cannot find image: " << name << endl;
    assert(!(resImage == NULL));
  }
  CLVisualImage *image = new CLVisualImage(resImage->get());
  image->setCenter((float) image->getWidth(vc_) / 2, 
                   (float) image->getHeight(vc_) / 2);
  return image;
}

BVisual *
CLResources::makeImage(ImagePart const part) {
  CLResImage *resImage = (CLResImage *) getImage(part.name);
  if (resImage == NULL) {
    cerr << "Cannot find image: " << part.name << endl;
    assert(!(resImage == NULL));
  }
  CLVisualImage *image = new CLVisualImage(resImage->get(), part.rect);
  image->setCenter((float) image->getWidth(vc_) / 2, 
                   (float) image->getHeight(vc_) / 2);
  return image;
}

BVisual *
CLResources::makeSprite(string const &name) {
  CLResSprite *resSprite = (CLResSprite *) getSprite(name);
  if (resSprite == NULL) {
    cerr << "Cannot find sprite: " << name << endl;
    assert(!(resSprite == NULL));
  }
  CL_Sprite *ret = new CL_Sprite();
  ret->clone(resSprite->get());
  CLVisualSprite *sprite = new CLVisualSprite(ret);
  sprite->setCenter((float) sprite->getWidth(vc_) / 2, 
                    (float) sprite->getHeight(vc_) / 2);
  return sprite;
}

BVisual *
CLResources::makeText(string const &text, string const &font, CPColor const &color) {
  CLResFont *resFont = (CLResFont *) getFont(font);
  if (resFont == NULL) {
    cerr << "Cannot find font: " << font << endl;
    assert(!(resFont == NULL));
  }
  CLVisualText *vtext =
    new CLVisualText(text, resFont->get(),
                     CL_Colorf(color.r, color.g, color.b, color.a));
  return vtext;
}

Audio *
CLResources::makeAudio(string const &audio, bool looping) {
  CLResAudio *resAudio = (CLResAudio *) getAudio(audio);
  if (resAudio == NULL) {
    cerr << "Cannot find audio: " << audio << endl;
    assert(!(resAudio == NULL));
  }
  return new CLAudio(audio, looping, resAudio->get());
}

string
CLResources::toString() const {
  ostringstream out;
  out << "{CLResources " << "???" << "}" << ends;
  return out.str();
}
