#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include "../Transform.h"
#include "SFMLRender.h"
#include "../BVisual.h"
#include "SFMLResources.h"
#include "SFMLVisualContext.h"

SFMLRender::SFMLRender(string const &name, EntityManager &em):
  Render(name, em), window(NULL) {
}

SFMLRender::~SFMLRender() {
}

void
SFMLRender::init() {
  window = new sf::RenderWindow(sf::VideoMode(640, 480, 32), "SFML chickenpix",
                                sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
  Entity *clstate = em.createEntity();
  clstate->addComponent(new SFMLResources(*window));
}

VisualContext *
SFMLRender::getVisualContext() {
  return new SFMLVisualContext(*window);
}

void
SFMLRender::clear(VisualContext &vc) {
  window->Clear(sf::Color(25, 100, 25));
  sf::Shape rect = sf::Shape::Rectangle(0, 0, 640, 280, sf::Color(95, 158, 160));
  window->Draw(rect);
}

void
SFMLRender::paint(VisualContext &vc) {
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
