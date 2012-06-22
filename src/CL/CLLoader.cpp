#include <iostream>
#include <sstream>
#include "CLLoader.h"
#include "CLResources.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"
#include "../Animated.h"
#include "../Input.h"
#include "../Scriptable.h"
#include "../Transform.h"

CLLoader::CLLoader(string const &name, EntityManager &em):
  System(name, em) {
}

CLLoader::~CLLoader() {
}

void
CLLoader::addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                    Resources *resources, string const &name) {
  resources->setSprite(name, new CLResSprite(new CL_SpriteDescription(gc, path, clresources)));;
}

void
CLLoader::init() {
  Resources *resources = em.getComponent<Resources>();
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  CL_GraphicContext &gc = vc.getGraphicContext();

  CL_PixelBuffer housePixBuf = CL_PNGProvider::load("resources/img/house.png");
  CL_Image *houseImg = new CL_Image(gc, housePixBuf, housePixBuf.get_size());
  resources->setImage("house", new CLResImage(houseImg));
  
  CL_ResourceManager clresources("resources/resources.xml");
  addSprite(gc, "sprites/walk_left", &clresources, resources, "man_walk_left");
  addSprite(gc, "sprites/walk_right", &clresources, resources, "man_walk_right");
  addSprite(gc, "sprites/walk_up", &clresources, resources, "man_walk_up");
  addSprite(gc, "sprites/walk_down", &clresources, resources, "man_walk_down");
  addSprite(gc, "sprites/wait", &clresources, resources, "man_still");

  resources->setFont("sans_big", new CLResFont(new CL_Font(gc, "Tahoma", 50)));
  resources->setFont("sans_small", new CLResFont(new CL_Font(gc, "Tahoma", 12)));
  
  Entity *e = em.createEntity();
  e->addComponent(new Transform(50, 150));
  e->addComponent(resources->makeImage("house"));

  e = em.createEntity();
  e->addComponent(new Transform(10, 300));
  e->addComponent(resources->makeSprite("man_walk_left"));

  Entity *hero = em.createEntity();
  hero->addComponent(new Transform(320, 222));
  hero->addComponent(new Animated("man_still"));
  hero->addComponent(new Input());
  hero->addComponent(new Scriptable("toby"));

  e = em.createEntity();
  e->addComponent(new Transform(100, 120));
  e->addComponent(resources->makeText("Chickenpix!", "sans_big"));
  //CL_Colorf(1.0f, 0.0f, 0.0f, 1.0f)));
  e = em.createEntity();
  e->addComponent(new Transform(5, 10));
  e->addComponent(resources->makeText("Press [ESC] to exit...", "sans_small"));
  //                                   CL_Colorf::white));
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
