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

  sf::Image *blurimg = new sf::Image();
  blurimg->LoadFromFile("resources/img/male_blur.png");
  blurimg->SetSmooth(false);
  frames.clear();
  for (int i = 0; i < 14; ++i) {
    frames.push_back(Frame(i * 64, 0, 64, 64, 100));
  }
  frames[0].duration = 4000;
  frames[13].duration = 1000;
  resources->setSprite("man_still", new SFMLResSprite(blurimg, frames, true));

    
  sf::Font *font = new sf::Font();
  if (!font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", 30)) {
    *font = sf::Font::GetDefaultFont();
  }
  ((sf::Image &)(font->GetImage())).SetSmooth(false);
  resources->setFont("sans_big", new SFMLResFont(font));
  font = new sf::Font();
  if (!font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", 8)) {
    *font = sf::Font::GetDefaultFont();
  }
  ((sf::Image &)(font->GetImage())).SetSmooth(false);
  resources->setFont("sans_small", new SFMLResFont(font));


  
  Entity *house = em.createEntity();
  house->addComponent(new Transform(50, 150));
  house->addComponent(resources->makeImage("house"));

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
