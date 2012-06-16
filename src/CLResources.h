#pragma once
#include <map>

#include <ClanLib/display.h>

#include "Component.h"

class CLResources : public Component {
private:
  map<string, CL_Image*> images;

  // I don't think it's a good idea to store CL_Sprite's because all users of a sprite will share the same state
  // (current frame, loop...). We should only store CL_SpriteDescription and create the CL_Sprite on demand
  map<string, CL_Sprite*> sprites;
public:
  static const Type TYPE = CLSPRITES_TYPE;

  CLResources();
  virtual ~CLResources();

  void addImage(string const &name, CL_Image *image);
  CL_Image *getImage(string const &name);
  void addSprite(string const &name, CL_Sprite *sprite);
  CL_Sprite *getSprite(string const &name);
  
  
  virtual string toString() const;
};
