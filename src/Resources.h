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
#include <map>

#include "Component.h"
#include "VisualContext.h"
#include "Audio.h"
#include "BVisual.h"
#include "Image.h"

// Abstract base classes to represent known types of resources
class ResBase {
public:
  virtual ~ResBase() {}
};
class ResImage: public ResBase {
public:
  virtual ~ResImage() {}
};
class ResSprite: public ResBase {
public:
  virtual ~ResSprite() {}
};
class ResFont: public ResBase {
public:
  virtual ~ResFont() {}
};
class ResAudio: public ResBase {
public:
  virtual ~ResAudio() {}
};
class CPColor {
public:
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;

  CPColor(unsigned char r, unsigned char g, unsigned char b,
          unsigned char a=255):
    r(r), g(g), b(b), a(a) {
  }
  
  CPColor(int r, int g, int b, int a=255):
    r((unsigned char) r),
    g((unsigned char) g),
    b((unsigned char) b),
    a((unsigned char) a) {
  }

  CPColor(float r, float g, float b, float a=1):
    r((unsigned char) (r * 255)),
    g((unsigned char) (g * 255)),
    b((unsigned char) (b * 255)),
    a((unsigned char) (a * 255)) {
  }

  CPColor(const CPColor &src):
    r(src.r), g(src.g), b(src.b), a(src.a) {
  }

  static CPColor White;
};


// Resource 'repository'
class Resources : public Component {
public:
  enum Kind {
    Image = 0,
    Sprite = 1,
    Font = 2,
    KAudio = 3
  };
  static const unsigned int KINDS = 4;
  
private:
  map<string, ResBase *> store[KINDS];

protected:
  void setObject(Kind kind, string const &name, ResBase *object);
  ResBase *getObject(Kind kind, string const &name);
  
public:
  static Type TYPE;

  Resources();
  virtual ~Resources();

  virtual VisualContext &getVisualContext() = 0;
  
  void setImage(string const &name, ResImage *image);
  ResImage *getImage(string const &name);
  void setSprite(string const &name, ResSprite *sprite);
  ResSprite *getSprite(string const &name);
  void setFont(string const &name, ResFont *font);
  ResFont *getFont(string const &name);
  void setAudio(string const &name, ResAudio *audio);
  ResAudio *getAudio(string const &name);

  // Factory methods to be implemented in specific implementations
  virtual BVisual *makeImage(string const &name) = 0;
  virtual BVisual *makeImage(ImagePart part) = 0;
  virtual BVisual *makeSprite(string const &name) = 0;
  virtual BVisual *makeText(string const &text, string const &font,
                            CPColor const &color=CPColor::White) = 0;
  virtual Audio *makeAudio(string const &name, bool looping) = 0;
  
  virtual string toString() const;
};

inline void Resources::setImage(string const &name, ResImage *image) {
  setObject(Resources::Image, name, image);
}
inline ResImage *Resources::getImage(string const &name) {
  return (ResImage *) getObject(Resources::Image, name);
}
inline void Resources::setSprite(string const &name, ResSprite *sprite) {
  setObject(Resources::Sprite, name, sprite);
}
inline ResSprite *Resources::getSprite(string const &name) {
  return (ResSprite *) getObject(Resources::Sprite, name);
}
inline void Resources::setFont(string const &name, ResFont *font) {
  setObject(Resources::Font, name, font);
}
inline ResFont *Resources::getFont(string const &name) {
  return (ResFont *) getObject(Resources::Font, name);
}
inline void Resources::setAudio(string const &name, ResAudio *audio) {
  setObject(Resources::KAudio, name, audio);
}
inline ResAudio *Resources::getAudio(string const &name) {
  return (ResAudio *) getObject(Resources::KAudio, name);
}
