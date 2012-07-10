#include <iostream>
#include <sstream>
#include "../log.h"
#include "../SystemRegistry.h"
#include "../TagEntityManager.h"
#include "../Transform.h"
#include "../BVisual.h"
#include "SFMLRender.h"
#include "SFMLResources.h"
#include "SFMLVisualContext.h"

// Init
bool SFMLRender::mWindowReady = false;

SFMLRender::SFMLRender(string const &name, unsigned int width, unsigned int height):
  Render( name), width_(width), height_(height), window_(NULL) {
}

SFMLRender::~SFMLRender() {
}

void
SFMLRender::init( EntityManager &em) {
  CTagEntityMng::TEntityId id = CTagEntityMng::get()->getEntityByTag( RENDER);
  Entity *clstate = em.getById( id);
  
  if ( !mWindowReady){
    window_ = new sf::RenderWindow(sf::VideoMode(width_, height_, 32), "SFML chickenpix",
                                   sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
     mWindowReady = true;
  }
  
  if ( !clstate){
    clstate = em.createEntity();
    clstate->addComponent(new SFMLResources(*window_));
  }
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
SFMLRender::exit( EntityManager&) {
  if (window_ != NULL) {
    window_->Close();
    delete window_;
    window_ = NULL;
  } else {
    LOG2 << "SFMLRender::exit has already been called\n";
  }
}

string
SFMLRender::toString() const {
  ostringstream out;
  out << "{SFMLRender-system name=" << getName() << " size=" << width_ << "x" << height_ << "}" <<ends;
  return out.str();
}
