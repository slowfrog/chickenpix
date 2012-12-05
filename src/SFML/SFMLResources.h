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

#include "SFML.h"
#include "../Image.h"
#include "../Resources.h"
#include "SFMLVisualContext.h"

class SFMLResImage: public ResImage {
private:
  sf::Image *image;
public:
  SFMLResImage(sf::Image *image);
  virtual ~SFMLResImage();
  sf::Image &get();
};
inline SFMLResImage::SFMLResImage(sf::Image *image):
  image(image) {
}
inline SFMLResImage::~SFMLResImage() {
  delete image;
}
inline sf::Image &SFMLResImage::get() {
  return *image;
}



class SFMLResSprite: public ResSprite {
private:
  sf::Image *image;
  vector<Frame> frames;
  bool pingpong;
public:
  SFMLResSprite(sf::Image *image, vector<Frame> const &frames, bool pingpong);
  virtual ~SFMLResSprite();
  sf::Image &getImage();
  vector<Frame> &getFrames();
  bool isPingPong() const;
};
inline SFMLResSprite::SFMLResSprite(sf::Image *image, vector<Frame> const &frames,
                                    bool pingpong=false):
  image(image), frames(frames), pingpong(pingpong) {
}
inline SFMLResSprite::~SFMLResSprite() {
  delete image;
}
inline sf::Image &SFMLResSprite::getImage() {
  return *image;
}
inline vector<Frame> &SFMLResSprite::getFrames() {
  return frames;
}
inline bool SFMLResSprite::isPingPong() const {
  return pingpong;
}


class SFMLResFont: public ResFont {
private:
  sf::Font *font;
public:
  SFMLResFont(sf::Font *font);
  virtual ~SFMLResFont();
  sf::Font &get();
};
inline SFMLResFont::SFMLResFont(sf::Font *font):
  font(font) {
}
inline SFMLResFont::~SFMLResFont() {
  delete font;
}
inline sf::Font &SFMLResFont::get() {
  return *font;
}

class SFMLResAudio: public ResAudio {
private:
  sf::SoundBuffer *sound_;
public:
  SFMLResAudio(sf::SoundBuffer *sound);
  virtual ~SFMLResAudio();
  sf::SoundBuffer &get();
};
inline SFMLResAudio::SFMLResAudio(sf::SoundBuffer *sound):
  sound_(sound) {
}
inline SFMLResAudio::~SFMLResAudio() {
  delete sound_;
}
inline sf::SoundBuffer &SFMLResAudio::get() {
  return *sound_;
}


//
class SFMLResources: public Resources {
private:
  SFMLVisualContext vc_;
public:
  SFMLResources(sf::RenderWindow &rw);
  virtual ~SFMLResources();

  virtual VisualContext &getVisualContext();
  virtual BVisual *makeImage(string const &name) ;
  virtual BVisual *makeImage(ImagePart part) ;
  virtual BVisual *makeSprite(string const &name);
  virtual BVisual *makeText(string const &text, string const &font,
                            CPColor const &color=CPColor::White);
  virtual Audio *makeAudio(string const &name, bool looping);

  virtual string toString() const;
};


