#include <iostream>
#include <sstream>
#include "CLLoader.h"
#include "CLState.h"
#include "CLResources.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"
#include "Input.h"
#include "Transform.h"

CLLoader::CLLoader(string const &name, EntityManager &em):
  System(name, em) {
}

CLLoader::~CLLoader() {
}

void
CLLoader::addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                    CLResources *resources, string const &name) {
  CL_Sprite *sprite = new CL_Sprite(gc, path, clresources);
  resources->addSprite(name, sprite);
}

void
CLLoader::init() {
  CLState *clstate = em.getComponent<CLState>();
  CL_GraphicContext &gc = clstate->getGC();

  Entity *resourcesentity = em.createEntity();
  CLResources *resources = new CLResources();
  resourcesentity->addComponent(resources);
  
  CL_PixelBuffer housePixBuf = CL_PNGProvider::load("resources/img/house.png");
  CL_Image *houseImg = new CL_Image(gc, housePixBuf, housePixBuf.get_size());
  resources->addImage("house", houseImg);
  
  CL_ResourceManager clresources("resources/resources.xml");
  addSprite(gc, "sprites/walk_left", &clresources, resources, "walk_left");
  addSprite(gc, "sprites/walk_right", &clresources, resources, "walk_right");
  addSprite(gc, "sprites/walk_up", &clresources, resources, "walk_up");
  addSprite(gc, "sprites/walk_down", &clresources, resources, "walk_down");
  addSprite(gc, "sprites/wait", &clresources, resources, "wait");

  resources->addFont("sans_big", new CL_Font(gc, "Tahoma", 50));
  resources->addFont("sans_small", new CL_Font(gc, "Tahoma", 12));
  
  Entity *e = em.createEntity();
  e->addComponent(new Transform(50, 150));
  e->addComponent(new CLVisualImage(*houseImg));

  e = em.createEntity();
  e->addComponent(new Transform(10, 300));
  e->addComponent(new CLVisualSprite(*resources->getSprite("walk_left")));

  Entity *hero = em.createEntity();
  hero->addComponent(new Transform(320, 222));
  hero->addComponent(new CLVisualSprite(*resources->getSprite("walk_right")));
  hero->addComponent(new Input());

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
