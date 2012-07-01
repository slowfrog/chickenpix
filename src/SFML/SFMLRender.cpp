#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include "../Transform.h"
#include "SFMLRender.h"
#include "../BVisual.h"
#include "SFMLResources.h"
#include "SFMLVisualContext.h"

SFMLRender::SFMLRender(string const &name, EntityManager &em, unsigned int width, unsigned int height):
  Render(name, em), width_(width), height_(height), window_(NULL) {
}

SFMLRender::~SFMLRender() {
}

void
SFMLRender::init() {
  window_ = new sf::RenderWindow(sf::VideoMode(width_, height_, 32), "SFML chickenpix",
                                 sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
  Entity *clstate = _em.createEntity();
  clstate->addComponent(new SFMLResources(*window_));
}

VisualContext *
SFMLRender::getVisualContext() {
  return new SFMLVisualContext(*window_);
}

void
SFMLRender::clear(VisualContext &vc) {
  window_->Clear(sf::Color::Black);
}

void
SFMLRender::paint(VisualContext &vc) {
  window_->Display();
}

void
SFMLRender::exit() {
  window_->Close();
  delete window_;
  window_ = NULL;
}

string
SFMLRender::toString() const {
  ostringstream out;
  out << "{SFMLRender-system name=" << getName() << " size=" << width_ << "x" << height_ << "}" <<ends;
  return out.str();
}
