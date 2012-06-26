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
  
  Resources *resources = em.getComponent<Resources>();
  addImage("resources/img/map.png", resources, "map");

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
Loader::loadLevel(string const &name) {
  Resources *resources = em.getComponent<Resources>();
  // Hard coded start level
  Entity *map = em.createEntity();
  map->addComponent(new Transform(-50, -50));
  map->addComponent(resources->makeImage("map"));

  Entity *male = em.createEntity();
  male->addComponent(new Transform(10, 300));
  male->addComponent(resources->makeSprite("man_walk_left"));

  Entity *hero = em.createEntity();
  hero->addComponent(new Transform(320, 222));
  hero->addComponent(new Animated("man_still"));
  hero->addComponent(new Input());
  hero->addComponent(new Scriptable("toto"));
  
  Entity *text = em.createEntity();
  text->addComponent(new Transform(100, 160));
  text->addComponent(resources->makeText("Chickenpix!", "sans_big", CPColor(255, 255, 0, 128)));
  text = em.createEntity();
  text->addComponent(new Transform(5, 10));
  text->addComponent(resources->makeText("Press [ESC] to quit...", "sans_small"));
}

string
Loader::toString() const {
  ostringstream out;
  out << "{Loader-system name=" << getName() << "}" << ends;
  return out.str();
}
