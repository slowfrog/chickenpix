#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include "SFMLRender.h"
#include "Transform.h"
#include "SFMLVisual.h"

SFMLRender::SFMLRender(string const &name, EntityManager &em):
  System(name, em), window(NULL) {
}

SFMLRender::~SFMLRender() {
}

void
SFMLRender::init() {
  window = new sf::RenderWindow(sf::VideoMode(640, 400, 32), "SFML chickenpix",
                                sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
}

void
SFMLRender::update(int now) {
  sf::Event event;
  while (window->GetEvent(event)) { // Should go into SFMLInputs
    if (event.Type == sf::Event::Closed) {
      //exitRequested = true;
    }
  }

  window->Clear(sf::Color(0, 100, 0));
  
  // CLVisual
  vector<Entity *> visuals = em.getEntities(SFMLVisual::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = visuals.begin(); it < visuals.end(); it++) {
    Entity *entity = *it;
    Transform *t = entity->getComponent<Transform>();
    SFMLVisual *v = entity->getComponent<SFMLVisual>();

    v->render(*window, t->getX(), t->getY());
  }
  
  window->Display();
}

void
SFMLRender::exit() {
  window->Close();
  delete window;
  window = NULL;
}

string
SFMLRender::toString() const {
  ostringstream out;
  out << "{SFMLRender-system name=" << getName() << ends;
  return out.str();
}
