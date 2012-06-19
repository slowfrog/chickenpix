#pragma once

#include <ClanLib/display.h>

#include "Resources.h"
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
  CL_SpriteDescription *sprite;
public:
  CLResSprite(CL_SpriteDescription *sprite);
  virtual ~CLResSprite();
  CL_SpriteDescription &get();
};
inline CLResSprite::CLResSprite(CL_SpriteDescription *sprite):
  sprite(sprite) {
}
inline CLResSprite::~CLResSprite() {
  delete sprite;
}
inline CL_SpriteDescription &CLResSprite::get() {
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



//
class CLResources: public Resources {
public:
  CLResources();
  virtual ~CLResources();

  virtual BVisual *makeImage(VisualContext &vc, string const &name) ;
  virtual BVisual *makeSprite(VisualContext &vc, string const &name);
  virtual BVisual *makeText(VisualContext &vc, string const &text, string const &font);

  virtual string toString() const;
};

