#include <iostream>
#include <sstream>
#include "CLLoader.h"
#include "CLState.h"
#include "CLResources.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"
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

  Entity *resourcesentity = em.createEntity();
  CLResources *resources = new CLResources();
  resourcesentity->addComponent(resources);
  
  CL_PixelBuffer housePixBuf = CL_PNGProvider::load("img/house.png");
  CL_Image *houseImg = new CL_Image(gc, housePixBuf, housePixBuf.get_size());
  resources->addImage("house", houseImg);
  
  CL_PixelBuffer maleWalkPixBuf = CL_PNGProvider::load("img/male_walkcycle.png");
  CL_SpriteDescription maleWalkRightDesc;
  maleWalkRightDesc.add_gridclipped_frames(maleWalkPixBuf, 0, 192, 64, 64, 9, 1);
  CL_Sprite *walkRightSprite = new CL_Sprite(gc, maleWalkRightDesc);
  walkRightSprite->set_delay(100);
  walkRightSprite->set_play_loop(true);
  resources->addSprite("walk_right", walkRightSprite);
  
  CL_SpriteDescription maleWalkLeftDesc;
  maleWalkLeftDesc.add_gridclipped_frames(maleWalkPixBuf, 0, 64, 64, 64, 9, 1);
  CL_Sprite *walkLeftSprite = new CL_Sprite(gc, maleWalkLeftDesc);
  walkLeftSprite->set_delay(100);
  walkLeftSprite->set_play_loop(true);
  resources->addSprite("walk_left", walkLeftSprite);

  resources->addFont("sans_big", new CL_Font(gc, "Tahoma", 50));
  resources->addFont("sans_small", new CL_Font(gc, "Tahoma", 12));


  
  Entity *e = em.createEntity();
  e->addComponent(new Transform(50, 150));
  e->addComponent(new CLVisualImage(*houseImg));

  e = em.createEntity();
  e->addComponent(new Transform(10, 300));
  e->addComponent(new CLVisualSprite(*walkRightSprite));

  e = em.createEntity();
  e->addComponent(new Transform(100, 120));
  e->addComponent(new CLVisualText("Chickenpix!",
                                   *resources->getFont("sans_big"),
                                   CL_Colorf(1.0f, 0.0f, 0.0f, 1.0f)));
  e = em.createEntity();
  e->addComponent(new Transform(5, 10));
  e->addComponent(new CLVisualText("Press [ESC] to exit...",
                                   *resources->getFont("sans_small"),
                                   CL_Colorf::white));
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
