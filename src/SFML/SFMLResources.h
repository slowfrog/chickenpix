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


//
class SFMLResources: public Resources {
private:
  SFMLVisualContext vc;
public:
  SFMLResources(sf::RenderWindow &rw);
  virtual ~SFMLResources();

  virtual VisualContext &getVisualContext();
  virtual BVisual *makeImage(string const &name) ;
  virtual BVisual *makeImage(ImagePart part) ;
  virtual BVisual *makeSprite(string const &name);
  virtual BVisual *makeText(string const &text, string const &font,
                            CPColor const &color=CPColor::White);

  virtual string toString() const;
};


