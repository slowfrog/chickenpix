#include <sstream>
#include "Loader.h"
#include "Transform.h"
#include "Animated.h"
#include "Input.h"
#include "Resources.h"
#include "Scriptable.h"


Loader::Loader(string const &name, EntityManager &em, string const &resourceFile):
  System(name, em), resourceFile(resourceFile) {
}

Loader::~Loader() {
}

void
Loader::init() {
  // Load resources
  initResources();
  
  Resources *resources = _em.getComponent<Resources>();
  addImage("resources/img/map.png", resources, "map");
  addImage("resources/img/cochon.png", resources, "pig");
  addImage("resources/img/garcon_des_rues.png", resources, "streetboy");
  addImage("resources/img/magicien.png", resources, "wizard");
  addImage("resources/img/maire.png", resources, "mayor");
  addImage("resources/img/princesse.png", resources, "princess");
  addImage("resources/img/richard.png", resources, "richard");

  addFont("resources/fonts/BerkshireSwash-Regular.ttf", 30, resources, "sans_big");
  addFont("resources/fonts/BerkshireSwash-Regular.ttf", 8, resources, "sans_small");

  addSprite("sprites/walk_up", resources, "man_walk_up");
  addSprite("sprites/walk_left", resources, "man_walk_left");
  addSprite("sprites/walk_down", resources, "man_walk_down");
  addSprite("sprites/walk_right", resources, "man_walk_right");
  addSprite("sprites/wait", resources, "man_still");

  // Load start level
  loadLevel("start");
}

void
Loader::update(int now) {
}

void
Loader::exit() {
}

void
Loader::createImage(string const &name, float x, float y, Resources *resources) {
  Entity *img = _em.createEntity();
  img->addComponent(new Transform(x, y));
  img->addComponent(resources->makeImage(name));
}

void
Loader::loadLevel(string const &name) {
  Resources *resources = _em.getComponent<Resources>();
  // Hard coded start level
  createImage("map", -150, -250, resources);

  createImage("pig", 10, 350, resources);
  createImage("streetboy", 50, 350, resources);
  createImage("mayor", 90, 350, resources);
  createImage("princess", 130, 350, resources);
  createImage("wizard", 170, 350, resources);
  createImage("richard", 210, 350, resources);

  Entity *hero = _em.createEntity();
  hero->addComponent(new Transform(320, 222));
  hero->addComponent(new Animated("man_still"));
  hero->addComponent(new Input());
  hero->addComponent(new Scriptable("toto"));
  _em.tagEntity(hero, "HERO");
  _em.tagEntity(hero, "DummyTag");
  
  Entity *text = _em.createEntity();
  text->addComponent(new Transform(100, 160));
  text->addComponent(resources->makeText("Chickenpix!", "sans_big", CPColor(255, 255, 0, 128)));
  _em.tagEntity(text, "LABEL");
  text = _em.createEntity();
  text->addComponent(new Transform(5, 10));
  text->addComponent(resources->makeText("Press [ESC] to quit...", "sans_small"));
  _em.tagEntity(text, "LABEL");
}

string
Loader::toString() const {
  ostringstream out;
  out << "{Loader-system name=" << getName() << "}" << ends;
  return out.str();
}
