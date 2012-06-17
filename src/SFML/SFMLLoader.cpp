#include <iostream>
#include <sstream>

#include "SFMLLoader.h"
#include "Transform.h"
#include "SFMLVisualImage.h"

SFMLLoader::SFMLLoader(string const &name, EntityManager &em):
  System(name, em) {
}

SFMLLoader::~SFMLLoader() {
}

void
SFMLLoader::init() {
  sf::Image &houseimg = *(new sf::Image()); // I know this is a memory leak. I'll put that in resources later
  if (!houseimg.LoadFromFile("resources/img/house.png")) {
    cerr << "Error loading resources/img/house.png" << endl;
    return;
  }
  sf::Sprite housesprite(houseimg);

  Entity *house = em.createEntity();

  house->addComponent(new Transform(50, 150));
  house->addComponent(new SFMLVisualImage(housesprite));
}

void
SFMLLoader::update(int now) {
}

void
SFMLLoader::exit() {
}

string
SFMLLoader::toString() const {
  ostringstream out;
  out << "{SFMLLoader-system name=" << getName() << "}" << ends;
  return out.str();
}
