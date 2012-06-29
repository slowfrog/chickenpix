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



//
class CLResources: public Resources {
private:
  CLVisualContext vc;
public:
  CLResources(CL_DisplayWindow &window);
  virtual ~CLResources();

  virtual VisualContext &getVisualContext();
  virtual BVisual *makeImage(string const &name) ;
  virtual BVisual *makeImage(ImagePart part) ;
  virtual BVisual *makeSprite(string const &name);
  virtual BVisual *makeText(string const &text, string const &font,
                            CPColor const &color=CPColor::White);

  virtual string toString() const;
};

