#pragma once
#include <map>

#include <ClanLib/display.h>

#include "Component.h"

class CLSprites : public Component {
private:
  map<string, CL_Sprite*> resources;
public:
  static const Type TYPE = CLSPRITES_TYPE;

  CLSprites();
  virtual ~CLSprites();

  void addSprite(string const &name, CL_Sprite *sprite);
  CL_Sprite *getSprite(string const &name);
  
  virtual string toString() const;
};
