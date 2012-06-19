#include <iostream>
#include <sstream>

#include "SFMLLoader.h"
#include "Input.h"
#include "Resources.h"
#include "Transform.h"
#include "SFMLResources.h"
#include "SFMLState.h"
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
  SFMLState *sfmlstate = em.getComponent<SFMLState>();
  sf::RenderTarget &rt = sfmlstate->getWindow();
  SFMLVisualContext vc(rt);
  
  Entity *resourcesentity = em.createEntity();
  Resources *resources = new SFMLResources();
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
  resources->setSprite("walk_left", new SFMLResSprite(maleimg, frames));
  for (int i = 0; i < 9; ++i) {
    frames[i] = Frame(i * 64, 192, 64, 64, 100);
  }
  resources->setSprite("walk_right", new SFMLResSprite(maleimg, frames));
  for (int i = 0; i < 9; ++i) {
    frames[i] = Frame(i * 64, 0, 64, 64, 100);
  }
  resources->setSprite("walk_up", new SFMLResSprite(maleimg, frames));
  for (int i = 0; i < 9; ++i) {
    frames[i] = Frame(i * 64, 128, 64, 64, 100);
  }
  resources->setSprite("walk_down", new SFMLResSprite(maleimg, frames));

    
  sf::Font *font = new sf::Font();
  if ( !font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", 30) ){
		*font = sf::Font::GetDefaultFont();
	}
  ((sf::Image &)(font->GetImage())).SetSmooth(false);
  resources->setFont("sans_big", new SFMLResFont(font));


  
  Entity *house = em.createEntity();
  house->addComponent(new Transform(50, 150));
  house->addComponent(resources->makeImage(vc, "house"));

  Entity *male = em.createEntity();
  male->addComponent(new Transform(10, 300));
  male->addComponent(resources->makeSprite(vc, "walk_left"));

  Entity *hero = em.createEntity();
  hero->addComponent(new Transform(320, 222));
  hero->addComponent(resources->makeSprite(vc, "walk_right"));
  hero->addComponent(new Input());
  
  Entity *text = em.createEntity();
  text->addComponent(new Transform(20, 40));
  text->addComponent(resources->makeText(vc, "Press [ESC] to quit...", "sans_big"));
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
