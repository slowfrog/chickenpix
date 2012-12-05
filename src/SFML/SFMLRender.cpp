/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
  if (window_ == NULL) {
    window_ = new sf::RenderWindow(sf::VideoMode(width_, height_, 32),
                                   "SFML chickenpix",
                                   sf::Style::Titlebar | sf::Style::Resize |
                                   sf::Style::Close);
    mWindowReady = true;
  }
  
  Entity *clstate = em.createEntity();
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
