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
 
#pragma once
#include "CL.h"
#include "../Resources.h"
#include "CLVisualContext.h"

// Concrete ClanLib resources
class CLResImage: public ResImage {
private:
  CL_Image *image;
public:
  CLResImage(CL_Image *image);
  virtual ~CLResImage();
  CL_Image &get();
};
inline CLResImage::CLResImage(CL_Image *image):
  image(image) {
}
inline CLResImage::~CLResImage() {
  delete image;
}
inline CL_Image &CLResImage::get() {
  return *image;
}



class CLResSprite: public ResSprite {
private:
  CL_Sprite *sprite;
public:
  CLResSprite(CL_Sprite *sprite);
  virtual ~CLResSprite();
  CL_Sprite &get();
};
inline CLResSprite::CLResSprite(CL_Sprite *sprite):
  sprite(sprite) {
}
inline CLResSprite::~CLResSprite() {
  delete sprite;
}
inline CL_Sprite &CLResSprite::get() {
  return *sprite;
}


class CLResFont: public ResFont {
private:
  CL_Font *font;
public:
  CLResFont(CL_Font *font);
  virtual ~CLResFont();
  CL_Font &get();
};
inline CLResFont::CLResFont(CL_Font *font):
  font(font) {
}
inline CLResFont::~CLResFont() {
  delete font;
}
inline CL_Font &CLResFont::get() {
  return *font;
}

class CLResAudio: public ResAudio {
private:
  CL_SoundBuffer *audio;
public:
  CLResAudio(CL_SoundBuffer *audio);
  virtual ~CLResAudio();
  CL_SoundBuffer &get();
};
inline CLResAudio::CLResAudio(CL_SoundBuffer *audio):
  audio(audio) {
}
inline CLResAudio::~CLResAudio() {
  delete audio;
}
inline CL_SoundBuffer &CLResAudio::get() {
  return *audio;
}


//
class CLResources: public Resources {
private:
  CLVisualContext vc_;
public:
  CLResources(CL_DisplayWindow &window);
  virtual ~CLResources();

  virtual VisualContext &getVisualContext();
  virtual BVisual *makeImage(string const &name) ;
  virtual BVisual *makeImage(ImagePart part) ;
  virtual BVisual *makeSprite(string const &name);
  virtual BVisual *makeText(string const &text, string const &font,
                            CPColor const &color=CPColor::White);
  virtual Audio *makeAudio(string const &audio, bool looping);

  virtual string toString() const;
};
