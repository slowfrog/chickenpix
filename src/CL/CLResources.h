#pragma once
#include <map>

#include <ClanLib/display.h>

#include "Resources.h"

class CLResources : public Resources {
public:
  CLResources();
  virtual ~CLResources();

  inline void setImage(string const &name, CL_Image *image) {
    setObject(Image, name, image);
  }
  inline CL_Image *getImage(string const &name) {
    return (CL_Image *) getObject(Image, name);
  }
  inline void setSprite(string const &name, CL_Sprite *sprite) {
    setObject(Sprite, name, sprite);
  }
  inline CL_Sprite *getSprite(string const &name) {
    return (CL_Sprite *) getObject(Sprite, name);
  }
  inline void setFont(string const &name, CL_Font *font) {
    setObject(Font, name, font);
  }
  inline CL_Font *getFont(string const &name) {
    return (CL_Font *) getObject(Font, name);
  }
  
  virtual string toString() const;
};
