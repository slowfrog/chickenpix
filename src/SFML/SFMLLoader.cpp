#include <iostream>
#include <sstream>

#include "SFMLLoader.h"
#include "Transform.h"
#include "SFMLVisualImage.h"
#include "SFMLVisualText.h"

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
  houseimg.SetSmooth(false);
  sf::Sprite housesprite(houseimg);

  Entity *house = em.createEntity();

  house->addComponent(new Transform(50, 150));
  house->addComponent(new SFMLVisualImage(housesprite));


  sf::Font *font = new sf::Font(); // Another memory leak
  if ( !font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", 30) ){
		*font = sf::Font::GetDefaultFont();
	}
	else {
		((sf::Image &)(font->GetImage())).SetSmooth(false);
	}

  
  Entity *text = em.createEntity();
  text->addComponent(new Transform(20, 40));
  text->addComponent(new SFMLVisualText("Press [ESC] to quit...",  *font, sf::Color(255, 255, 0)));
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
