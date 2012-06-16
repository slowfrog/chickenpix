#include <iostream>
#include <sstream>
#include "CLLoader.h"
#include "CLState.h"
#include "CLSprites.h"

CLLoader::CLLoader(string const &name, EntityManager &em):
  System(name, em) {
}

CLLoader::~CLLoader() {
}

void
CLLoader::init() {
  CLState *clstate = em.getComponent<CLState>();
  CL_GraphicContext &gc = clstate->getGC();

  Entity *clspritesentity = em.createEntity();
  CLSprites *clsprites = new CLSprites();
  clspritesentity->addComponent(clsprites);
  
  CL_PixelBuffer housePixBuf = CL_PNGProvider::load("house.png");
  CL_Image houseImg(gc, housePixBuf, housePixBuf.get_size());
  
  CL_PixelBuffer maleWalkPixBuf = CL_PNGProvider::load("male_walkcycle.png");
  CL_SpriteDescription maleWalkRightDesc;
  maleWalkRightDesc.add_gridclipped_frames(maleWalkPixBuf, 0, 192, 64, 64, 9, 1);
  CL_Sprite *walkRightSprite = new CL_Sprite(gc, maleWalkRightDesc);
  walkRightSprite->set_delay(100);
  walkRightSprite->set_play_loop(true);
  clsprites->addSprite("walk_right", walkRightSprite);
  
  CL_SpriteDescription maleWalkLeftDesc;
  maleWalkLeftDesc.add_gridclipped_frames(maleWalkPixBuf, 0, 64, 64, 64, 9, 1);
  CL_Sprite *walkLeftSprite = new CL_Sprite(gc, maleWalkLeftDesc);
  walkLeftSprite->set_delay(100);
  walkLeftSprite->set_play_loop(true);
  clsprites->addSprite("walk_left", walkLeftSprite);
  
  cout << "Everything loaded" << endl;
}

void
CLLoader::update(int now) {
}

void
CLLoader::exit() {
}

string
CLLoader::toString() const {
  ostringstream out;
  out << "{CLLoader-System name=" << getName() << "}" << ends;
  return out.str();
}
