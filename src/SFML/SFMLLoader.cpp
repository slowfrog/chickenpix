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
  Loader(name, em) {
}

SFMLLoader::~SFMLLoader() {
}

void
SFMLLoader::addImage(VisualContext &vc, string const &path, Resources *resources,
                     string const &alias) {
  sf::Image *img = new sf::Image();
  if (!img->LoadFromFile(path)) {
    cerr << "Error loading image: " << path << endl;
    return;
  }
  img->SetSmooth(false);
  resources->setImage(path, new SFMLResImage(img));
  if (alias.length() > 0) {
    resources->setImage(alias, new SFMLResImage(img));
  }
}

void
SFMLLoader::addFont(VisualContext &vc, string const &path, int size, Resources *resources,
                     string const &alias) {
  sf::Font *font = new sf::Font();
  if (!font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", size)) {
    cerr << "Error loading font: " << path << endl;
    *font = sf::Font::GetDefaultFont();
  }
  ((sf::Image &)(font->GetImage())).SetSmooth(false);
  resources->setFont(path, new SFMLResFont(font));
  if (alias.length() > 0) {
    resources->setFont(alias, new SFMLResFont(font));
  }
}

void
SFMLLoader::init() {
  Loader::init();
  
  Resources *resources = em.getComponent<Resources>();
  
  Entity *resourcesentity = em.createEntity();
  resourcesentity->addComponent(resources);

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

  loadLevel("start");
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
