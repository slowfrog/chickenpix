#include <sstream>
#include "Loader.h"
#include "Transform.h"
#include "Animated.h"
#include "Input.h"
#include "Resources.h"
#include "Scriptable.h"


Loader::Loader(string const &name, EntityManager &em):
  System(name, em) {
}

Loader::~Loader() {
}

void
Loader::init() {
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
  Entity *house = em.createEntity();
  house->addComponent(new Transform(50, 150));
  house->addComponent(resources->makeImage("house"));

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
