#include <iostream>
#include <sstream>

#include "SFMLLoader.h"
#include "../Animated.h"
#include "../Input.h"
#include "../Resources.h"
#include "../Scriptable.h"
#include "../Transform.h"
#include "SFMLResources.h"
#include "SFMLVisualContext.h"
#include "SFMLVisualImage.h"
#include "SFMLVisualText.h"

SFMLLoader::SFMLLoader(string const &name, EntityManager &em):
  System(name, em) {
}

SFMLLoader::~SFMLLoader() {
}

void
SFMLLoader::init() {
  Resources *resources = em.getComponent<Resources>();
  
  Entity *resourcesentity = em.createEntity();
  resourcesentity->addComponent(resources);
  
  sf::Image *houseimg = new sf::Image();
  if (!houseimg->LoadFromFile("resources/img/house.png")) {
    cerr << "Error loading resources/img/house.png" << endl;
    return;
  }
  houseimg->SetSmooth(false);
  resources->setImage("house", new SFMLResImage(houseimg));

  sf::Image *maleimg = new sf::Image();
  maleimg->LoadFromFile("resources/img/male_walkcycle.png");
  maleimg->SetSmooth(false);
  vector<Frame> frames;
  for (int i = 0; i < 9; ++i) {
    frames.push_back(Frame(i * 64, 64, 64, 64, 100));
  }
  resources->setSprite("man_walk_left", new SFMLResSprite(maleimg, frames));
  for (int i = 0; i < 9; ++i) {
    frames[i] = Frame(i * 64, 192, 64, 64, 100);
  }
  resources->setSprite("man_walk_right", new SFMLResSprite(maleimg, frames));
  for (int i = 0; i < 9; ++i) {
    frames[i] = Frame(i * 64, 0, 64, 64, 100);
  }
  resources->setSprite("man_walk_up", new SFMLResSprite(maleimg, frames));
  for (int i = 0; i < 9; ++i) {
    frames[i] = Frame(i * 64, 128, 64, 64, 100);
  }
  resources->setSprite("man_walk_down", new SFMLResSprite(maleimg, frames));
  frames.erase(frames.begin() + 1, frames.end());
  resources->setSprite("man_still", new SFMLResSprite(maleimg, frames)); // Not really still

    
  sf::Font *font = new sf::Font();
  if ( !font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", 30) ){
		*font = sf::Font::GetDefaultFont();
	}
  ((sf::Image &)(font->GetImage())).SetSmooth(false);
  resources->setFont("sans_big", new SFMLResFont(font));


  
  Entity *house = em.createEntity();
  house->addComponent(new Transform(50, 150));
  house->addComponent(resources->makeImage("house"));

  Entity *male = em.createEntity();
  male->addComponent(new Transform(10, 300));
  male->addComponent(resources->makeSprite("man_walk_left"));

  Entity *hero = em.createEntity();
  hero->addComponent(new Transform(320, 222));
  hero->addComponent(new Animated("man_walk_right"));
  hero->addComponent(new Input());
  hero->addComponent(new Scriptable("toto"));
  
  Entity *text = em.createEntity();
  text->addComponent(new Transform(20, 40));
  text->addComponent(resources->makeText("Press [ESC] to quit...", "sans_big"));
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
