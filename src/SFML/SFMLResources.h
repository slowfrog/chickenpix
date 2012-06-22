#pragma once

#include <SFML/Graphics.hpp>

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
public:
  SFMLResSprite(sf::Image *image, vector<Frame> const &frames);
  virtual ~SFMLResSprite();
  sf::Image &getImage();
  vector<Frame> &getFrames();
};
inline SFMLResSprite::SFMLResSprite(sf::Image *image, vector<Frame> const &frames):
  image(image), frames(frames) {
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


//
class SFMLResources: public Resources {
private:
  SFMLVisualContext vc;
public:
  SFMLResources(sf::RenderWindow &rw);
  virtual ~SFMLResources();

  virtual VisualContext &getVisualContext();
  virtual BVisual *makeImage(string const &name) ;
  virtual BVisual *makeSprite(string const &name);
  virtual BVisual *makeText(string const &text, string const &font);

  virtual string toString() const;
};






