#include <iostream>
#include <sstream>
#include "CLLoader.h"
#include "CLState.h"
#include "CLSprites.h"
#include "CLVisual.h"
#include "Transform.h"

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
  CL_Image *houseImg = new CL_Image(gc, housePixBuf, housePixBuf.get_size());
  clsprites->addImage("house", houseImg);
  
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

  Entity *e = em.createEntity();
  e->addComponent(new Transform(50, 150));
  e->addComponent(new CLVisual(houseImg));

  e = em.createEntity();
  e->addComponent(new Transform(10, 300));
  e->addComponent(new CLVisual(walkRightSprite));
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
